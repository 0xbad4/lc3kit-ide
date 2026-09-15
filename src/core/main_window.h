#pragma once
#include "panels/all.h"
#include "widgets/wmain_window.h"
#include "utils/logger.h"
#include "utils/manifest.h"
#include "dialogs/about.h"
#include "core/tab_man.h"
#include "core/machine_man.h"
#include "core/custom_win_bar.h"

#include <QDesktopServices>
#include <QUrl>


namespace lc3kit::ide
{
    class MainWindow : public QMainWindow {
        Q_OBJECT

        public:
            inline static QString NAME = "IDE";

            explicit MainWindow() : QMainWindow(), m_main(new Ui::MainWindow) {}

            void init() {
                qDebug() << NAME << ": constructing main window";
                setup_window();
                setup_menu_bar();
                setup_elements();
                setup_icons();
                setup_signals();
                setup_machine_man();
                setup_theme();

                qInfo() << NAME << ": main window initialized — ready for display";

                emit ready(this);
            }

            ~MainWindow() {
                if (m_main) {
                    delete m_main;
                }
            }

        signals:
            void ready(MainWindow*);

        protected:
            Ui::MainWindow* m_main = nullptr;
            DragMenuBar*  m_d_menu_bar = nullptr;

            // ----------- Men
            TabManager*     m_tabs_man_ptr = nullptr;
            MachineManager* m_machine_man_ptr = nullptr;

            // ----------- Panels
            Breakpoints*   m_breakpoints_pptr = nullptr;
            Console*       m_console_pptr     = nullptr;
            FlagsRegister* m_flags_pptr       = nullptr;
            Logs*          m_logs_pptr        = nullptr;
            MemoryView*    m_memory_pptr      = nullptr;
            Registers*     m_registers_pptr   = nullptr;
            Settings*      m_settings_pptr    = nullptr;
            SymTable*      m_symtab_pptr      = nullptr;

            void closeEvent(QCloseEvent* event) override {
                qInfo() << NAME << ": main window closing initiated";

                if (m_machine_man_ptr) {
                    qDebug() << NAME << ": stopping VM if currently running";
                    m_machine_man_ptr->stop();
                    qDebug() << NAME << ": VM stopped";
                }

                if (m_tabs_man_ptr->is_there_unsaved()) {
                    // Canceled, don't exit
                    if (m_tabs_man_ptr->ask_to_save()) {
                        event->ignore();
                        return;
                    }
                }

                // persist window layout for next session
                qDebug() << NAME << ": saving window geometry and state";
                QSettings settings("lc3kit-ide", "IDE");
                settings.setValue("window/geometry", saveGeometry());
                settings.setValue("window/state",    saveState());
                qDebug() << NAME << ": window geometry and state persisted";

                qInfo() << NAME << ": application shutdown complete";
                QMainWindow::closeEvent(event);
            }

            void set_custom_dock_bar(QDockWidget* dock) {
                auto* bar = new QWidget(dock);
                bar->setObjectName("dock-title-bar");

                auto* layout = new QHBoxLayout(bar);
                layout->setContentsMargins(8, 4, 4, 4);
                layout->setSpacing(2);

                auto* title = new QLabel(dock->windowTitle(), bar);
                title->setObjectName("dock-title-label");
                layout->addWidget(title);
                layout->addStretch();

                QToolButton* float_btn = nullptr;
                if (dock->features() & QDockWidget::DockWidgetFloatable) {
                    float_btn = new QToolButton(bar);
                    float_btn->setObjectName("dock-float-button");
                    float_btn->setAutoRaise(true);
                    float_btn->setIcon(ICON("dock-restore"));

                    QObject::connect(dock, &QDockWidget::topLevelChanged, float_btn,
                        [float_btn](bool floating) {
                            float_btn->setIcon(ICON("dock-restore"));
                        });

                    QObject::connect(float_btn, &QToolButton::clicked, dock, [dock]() {
                        dock->setFloating(!dock->isFloating());
                    });

                    layout->addWidget(float_btn);
                }

                QToolButton* close_btn = nullptr;
                if (dock->features() & QDockWidget::DockWidgetClosable) {
                    close_btn = new QToolButton(bar);
                    close_btn->setObjectName("dock-close-button");
                    close_btn->setAutoRaise(true);
                    close_btn->setIcon(ICON("dock-close"));
                    QObject::connect(close_btn, &QToolButton::clicked, dock, &QDockWidget::close);
                    layout->addWidget(close_btn);
                }

                QObject::connect(dock, &QDockWidget::windowTitleChanged, title, &QLabel::setText);

                dock->setTitleBarWidget(bar);
            }

            void setup_window() {
                m_main->setupUi(this);

                // window properties
                setWindowTitle("LC3kit - IDE");
                setMinimumSize(1024, 600);
                resize(1440, 900);
                setWindowIcon(QIcon(":/img/lc3kit-ide"));

                // center on screen
                QScreen* screen = QGuiApplication::primaryScreen();

                if (screen) {
                    QRect geo = screen->availableGeometry();
                    move(geo.center() - rect().center());
                }

                // restore geometry from last session #0d1117
                QSettings settings("lc3kit-ide", "IDE");

                if (settings.contains("window/geometry")) {
                    restoreGeometry(settings.value("window/geometry").toByteArray());
                }
                if (settings.contains("window/state")) {
                    restoreState(settings.value("window/state").toByteArray());
                }

                // window flags
                setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

                // drag and drop — accept .asm files
                setAcceptDrops(true);

                // status bar
                statusBar()->setSizeGripEnabled(true);
            }

            void setup_menu_bar() {
                m_d_menu_bar = new DragMenuBar(this);

                for (QDockWidget *dock : findChildren<QDockWidget *>()) {
                    m_d_menu_bar->menu_view->addAction(dock->toggleViewAction());
                }

                setMenuBar(m_d_menu_bar);
                
                m_d_menu_bar->setWindowTitle("Frame");
                m_main->toolbar->setWindowTitle("Tools");
                m_main->panelsbar->setWindowTitle("Panels");
                m_main->texteditbar->setWindowTitle("Text Edit");

                setup_help();
            }

            void setup_help() {
                // Documentation + Source
                connect(m_d_menu_bar->action_documentation, &QAction::triggered, [&](){
                    QDesktopServices::openUrl(QUrl(appmanifest.documentation()));
                });
                connect(m_d_menu_bar->action_source_code, &QAction::triggered, [&](){
                    QDesktopServices::openUrl(QUrl(appmanifest.source()));
                });

                // ASM examples
                qDebug() << "loading asm examples";

                for (const auto& exm : appmanifest.asm_examples()) {
                    auto* action = new QAction();
                    action->setProperty("filepath", exm);
                    action->setText(QFileInfo(exm).fileName());
                    connect(action, &QAction::triggered, this, &MainWindow::on_example_action_triggered);
                    m_d_menu_bar->menu_examples->addAction(action);
                }

                // About
                connect(m_d_menu_bar->action_about, &QAction::triggered, this, [this] { AboutDialog(this).exec(); });
            }

            void setup_elements() {
                m_tabs_man_ptr = new TabManager(m_main->text_editors_tab);
                m_breakpoints_pptr = new Breakpoints(m_main->breakpoints_tree);
                m_console_pptr = new Console(m_main->console_dockw_body);
                m_flags_pptr = new FlagsRegister(m_main->flags_dockw_body);
                m_logs_pptr = new Logs(m_main->logs_tree);
                m_memory_pptr = new MemoryView(m_main->memory_tree);
                m_registers_pptr = new Registers(m_main->registers_tree);
                m_settings_pptr = new Settings(m_main->settings_dockw_body);
                m_symtab_pptr = new SymTable(m_main->symtab_tree);

                set_custom_dock_bar(m_main->breakpoints_dockw);
                set_custom_dock_bar(m_main->console_dockw);
                set_custom_dock_bar(m_main->flags_dockw);
                set_custom_dock_bar(m_main->logs_dockw);
                set_custom_dock_bar(m_main->memory_dockw);
                set_custom_dock_bar(m_main->registers_dockw);
                set_custom_dock_bar(m_main->settings_dockw);
                set_custom_dock_bar(m_main->symtab_dockw);

                machine_exec_set_elements(false);
                m_main->action_break_point_continue->setDisabled(true);
            }

            void setup_icons() {
                m_main->action_open_file->setIcon(ICON("file-open"));
                m_main->action_new_file->setIcon(ICON("file-new"));
                m_main->action_save->setIcon(ICON("file-save"));
                m_main->action_save_as->setIcon(ICON("file-save-as"));

                m_main->action_assemble->setIcon(ICON("machine-assemble"));
                m_main->action_assemble_export->setIcon(ICON("machine-assemble-export"));
                m_main->action_run->setIcon(ICON("machine-run"));
                m_main->action_debug->setIcon(ICON("machine-debug"));

                m_main->action_stop->setIcon(ICON("machine-stop"));
                m_main->action_debug_next->setIcon(ICON("machine-debug-next"));
                m_main->action_break_point_continue->setIcon(ICON("machine-breakpoint-resume"));

                m_main->action_show_breakpoints->setIcon(ICON("panel-breakpoints"));
                m_main->action_show_console->setIcon(ICON("panel-console"));
                m_main->action_show_flags->setIcon(ICON("panel-flags"));
                m_main->action_show_logs->setIcon(ICON("panel-logs"));
                m_main->action_show_memory->setIcon(ICON("panel-memory"));
                m_main->action_show_registers->setIcon(ICON("panel-registers"));
                m_main->action_show_settings->setIcon(ICON("panel-settings"));
                m_main->action_show_symtab->setIcon(ICON("panel-symtab"));

                m_main->breakpoints_dockw->setWindowIcon(ICON("panel-breakpoints"));
                m_main->console_dockw->setWindowIcon(ICON("panel-console"));
                m_main->flags_dockw->setWindowIcon(ICON("panel-flags"));
                m_main->logs_dockw->setWindowIcon(ICON("panel-logs"));
                m_main->memory_dockw->setWindowIcon(ICON("panel-memory"));
                m_main->registers_dockw->setWindowIcon(ICON("panel-registers"));
                m_main->settings_dockw->setWindowIcon(ICON("panel-settings"));
                m_main->symtab_dockw->setWindowIcon(ICON("panel-symtab"));

                m_main->action_copy->setIcon(ICON("text-copy"));
                m_main->action_cut->setIcon(ICON("text-cut"));
                m_main->action_paste->setIcon(ICON("text-paste"));
                m_main->action_undo->setIcon(ICON("text-undo"));
                m_main->action_redo->setIcon(ICON("text-redo"));
                m_main->action_find->setIcon(ICON("text-search"));
            }

            void setup_signals() {
                // window
                connect(m_d_menu_bar->action_quit, &QAction::triggered, this, &MainWindow::close);
                connect(m_settings_pptr, &Settings::settings_changed, this, &MainWindow::on_settings_changed);

                // logs
                connect(Logger::instance(), &Logger::logged, m_logs_pptr, &Logs::log);

                // file management
                connect(m_main->action_open_file, &QAction::triggered, m_tabs_man_ptr, &TabManager::open_file);
                connect(m_main->action_new_file, &QAction::triggered, m_tabs_man_ptr, &TabManager::new_file);
                connect(m_main->action_save, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_save);
                connect(m_main->action_save_as, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_save_as);
                
                connect(m_d_menu_bar->action_open, &QAction::triggered, m_tabs_man_ptr, &TabManager::open_file);
                connect(m_d_menu_bar->action_new, &QAction::triggered, m_tabs_man_ptr, &TabManager::new_file);
                connect(m_d_menu_bar->action_save, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_save);
                connect(m_d_menu_bar->action_save_as, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_save_as);
                
                connect(m_d_menu_bar->action_close, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_close);
                connect(m_tabs_man_ptr, &TabManager::editor_saved, this, &MainWindow::on_editor_saved);

                // machine control
                connect(m_main->action_assemble, &QAction::triggered, this, &MainWindow::ac_current_assemble);
                connect(m_main->action_assemble_export, &QAction::triggered, this, &MainWindow::ac_current_export_assemble);
                connect(m_main->action_run, &QAction::triggered, this, &MainWindow::ac_current_run);
                connect(m_main->action_debug, &QAction::triggered, this, &MainWindow::ac_current_debug);

                connect(m_main->action_stop, &QAction::triggered, this, &MainWindow::ac_execution_stop);
                connect(m_main->action_debug_next, &QAction::triggered, this, &MainWindow::ac_execution_next);
                connect(m_main->action_break_point_continue, &QAction::triggered, this, &MainWindow::ac_execution_resume);

                connect(m_d_menu_bar->action_assemble, &QAction::triggered, this, &MainWindow::ac_current_assemble);
                connect(m_d_menu_bar->action_export_assembled, &QAction::triggered, this, &MainWindow::ac_current_export_assemble);
                connect(m_d_menu_bar->action_run, &QAction::triggered, this, &MainWindow::ac_current_run);
                connect(m_d_menu_bar->action_debug, &QAction::triggered, this, &MainWindow::ac_current_debug);
                connect(m_d_menu_bar->action_stop, &QAction::triggered, this, &MainWindow::ac_execution_stop);
                connect(m_d_menu_bar->action_step, &QAction::triggered, this, &MainWindow::ac_execution_next);
                connect(m_d_menu_bar->action_resume, &QAction::triggered, this, &MainWindow::ac_execution_resume);

                connect(m_d_menu_bar->action_toggle_breakpoint, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_toggle_breakpoint);
                connect(m_d_menu_bar->action_clear_breakpoints, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_clear_breakpoints);

                // panels visibility
                connect(m_main->action_show_breakpoints, &QAction::triggered, m_main->breakpoints_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_console, &QAction::triggered, m_main->console_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_flags, &QAction::triggered, m_main->flags_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_logs, &QAction::triggered, m_main->logs_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_memory, &QAction::triggered, m_main->memory_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_registers, &QAction::triggered, m_main->registers_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_settings, &QAction::triggered, m_main->settings_dockw, &QDockWidget::setVisible);
                connect(m_main->action_show_symtab, &QAction::triggered, m_main->symtab_dockw, &QDockWidget::setVisible);
                // reflection
                connect(m_main->breakpoints_dockw, &QDockWidget::visibilityChanged, m_main->action_show_breakpoints, &QAction::setChecked);
                connect(m_main->console_dockw, &QDockWidget::visibilityChanged, m_main->action_show_console, &QAction::setChecked);
                connect(m_main->flags_dockw, &QDockWidget::visibilityChanged, m_main->action_show_flags, &QAction::setChecked);
                connect(m_main->logs_dockw, &QDockWidget::visibilityChanged, m_main->action_show_logs, &QAction::setChecked);
                connect(m_main->memory_dockw, &QDockWidget::visibilityChanged, m_main->action_show_memory, &QAction::setChecked);
                connect(m_main->registers_dockw, &QDockWidget::visibilityChanged, m_main->action_show_registers, &QAction::setChecked);
                connect(m_main->settings_dockw, &QDockWidget::visibilityChanged, m_main->action_show_settings, &QAction::setChecked);
                connect(m_main->symtab_dockw, &QDockWidget::visibilityChanged, m_main->action_show_symtab, &QAction::setChecked);

                // text processing
                connect(m_main->action_copy, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_copy);
                connect(m_main->action_cut, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_cut);
                connect(m_main->action_paste, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_paste);
                connect(m_main->action_undo, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_undo);
                connect(m_main->action_redo, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_redo);
                connect(m_main->action_find, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_find);

                connect(m_d_menu_bar->action_copy_selection, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_copy);
                connect(m_d_menu_bar->action_copy_line, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_copy_line);
                connect(m_d_menu_bar->action_copy_all, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_copy_all);
                connect(m_d_menu_bar->action_copy_path, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_copy_path);
                
                connect(m_d_menu_bar->action_select_all, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_select_all);
                connect(m_d_menu_bar->action_cut, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_cut);
                connect(m_d_menu_bar->action_paste, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_paste);
                connect(m_d_menu_bar->action_undo, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_undo);
                connect(m_d_menu_bar->action_redo, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_redo);
                connect(m_d_menu_bar->action_find, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_find);

                connect(m_d_menu_bar->action_duplicate_line, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_duplicate);
                connect(m_d_menu_bar->action_move_up, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_up);
                connect(m_d_menu_bar->action_move_down, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_down);
                connect(m_d_menu_bar->action_go_to_line, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_goto);
                connect(m_d_menu_bar->action_delete_line, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_delete);
                connect(m_d_menu_bar->action_toggle_comment, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_comment);
                connect(m_d_menu_bar->action_trim_whitespace, &QAction::triggered, m_tabs_man_ptr, &TabManager::current_line_trim_whitespace);

                connect(m_d_menu_bar->action_open_settings, &QAction::triggered, [this]() {
                    m_main->settings_dockw->setVisible(true);
                    m_main->settings_dockw->show();
                    m_main->settings_dockw->raise();
                });

                // group boot mode
                auto action_group = new QActionGroup(this);
                action_group->setExclusive(true);
                action_group->addAction(m_main->action_mode_step_tog);
                action_group->addAction(m_main->action_mode_run_tog);
            }

            void setup_machine_man() {
                qDebug() << NAME << ": initializing machine manager and signal routing";
                
                if (!m_machine_man_ptr) {
                    m_machine_man_ptr = new MachineManager(this);
                }

                // VM register/memory change notifications
                connect(m_machine_man_ptr, &MachineManager::after_register_write, m_registers_pptr, &Registers::on_register_changed);
                connect(m_machine_man_ptr, &MachineManager::after_memory_write, m_registers_pptr, &Registers::on_memory_changed);
                connect(m_machine_man_ptr, &MachineManager::after_register_write, m_flags_pptr, &FlagsRegister::on_register_changed);
                connect(m_machine_man_ptr, &MachineManager::after_memory_write, m_memory_pptr, &MemoryView::on_memory_changed);
                connect(m_machine_man_ptr, &MachineManager::invalid_memory_access, m_memory_pptr, &MemoryView::on_memory_violation);
                connect(m_machine_man_ptr, &MachineManager::breakpoint, m_breakpoints_pptr, &Breakpoints::on_breakpoint);
                
                // Machine events to main window
                connect(m_machine_man_ptr, &MachineManager::after_instruction, this, &MainWindow::on_after_instruction);
                connect(m_machine_man_ptr, &MachineManager::execution_started, this, &MainWindow::on_execution_started);
                connect(m_machine_man_ptr, &MachineManager::execution_halted, this, &MainWindow::on_execution_halted);
                connect(m_machine_man_ptr, &MachineManager::breakpoint, this, &MainWindow::on_breakpoint);

                // Console I/O routing
                connect(m_machine_man_ptr, &MachineManager::console_output, m_console_pptr, &Console::on_console_output);
                connect(m_machine_man_ptr, &MachineManager::before_trap, m_console_pptr, &Console::on_before_trap);
                connect(m_machine_man_ptr, &MachineManager::after_trap, m_console_pptr, &Console::on_after_trap);
                connect(m_console_pptr, &Console::console_input, m_machine_man_ptr, &MachineManager::on_console_input, Qt::QueuedConnection);
                connect(m_console_pptr, &Console::run_requested, this, &MainWindow::ac_current_run);
                connect(m_console_pptr, &Console::debug_requested, this, &MainWindow::ac_current_debug);

                qDebug() << NAME << ": machine manager connected — ready for operations";
            }

            void setup_theme() {
                qDebug() << NAME << ": setting up theme";
                ((QApplication*)QApplication::instance())->setStyleSheet(lc3kit::ide::QSS());
            }

            // Slots
            void on_example_action_triggered() {
                if (!sender()) {
                    return;
                }

                const QString filepath = sender()->property("filepath").toString().remove(".asm");
                QFileInfo finfo(filepath);

                if (filepath.isEmpty()) {
                    return;
                }

                QFile file(filepath);

                if (!file.exists()) {
                    DLERROR(QString("Requested example not found: %1").arg(finfo.fileName()));
                    return;
                }

                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    DLERROR(QString("Could not open requested example: %1").arg(finfo.fileName()));
                    return;
                }

                const QByteArray content = file.readAll();
                file.close();

                const QString tmp_dir = QDir(QDir::tempPath()).filePath("lc3kit-examples");

                if (!QDir().mkpath(tmp_dir)) {
                    DLERROR(QString("Could not create temp directory '%1'").arg(tmp_dir));
                    return;
                }

                const QString tmp_path = QDir(tmp_dir).filePath(QFileInfo(filepath).fileName()) + ".asm";
                QFile tmp_file(tmp_path);

                if (!tmp_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                    DLERROR(QString("Could not create temporary file '%1'").arg(tmp_path));
                    return;
                }

                tmp_file.write(content);
                tmp_file.close();

                m_tabs_man_ptr->new_file_with_path(tmp_path);
            }

            void on_settings_changed(qsetting_key k, QVariant v) {
                if (k == THEME_NAME) {
                    theman.theme(v.toString().toLower());
                    m_tabs_man_ptr->change_editors_theme();
                    setup_theme();
                    // reset icons
                    setup_icons();
                }
            }

            void on_editor_saved(TextEditor* editor) {
                if (!editor) {
                    return;
                }

                if (settings.get_bool(ASM_ON_SAVE)) {
                    qDebug() << NAME << ": Assemble on save";
                    m_machine_man_ptr->assemble({editor});
                }

            }

            void on_execution_started(vm_ptr_t rvm, TextEditor* editor) {
                qDebug() << NAME << ": execution started — UI mode changed to running";
                machine_exec_set_elements(true);

                qInfo() << NAME << ": loading panels with VM state";

                m_console_pptr->load(rvm);
                m_memory_pptr->load(rvm);
                m_registers_pptr->load(rvm);
                m_flags_pptr->load(rvm);
                m_symtab_pptr->load(editor->asm_obj().symtab, editor->asm_obj().linesaddrs);
                m_breakpoints_pptr->load(editor->breakpoints_addrs(), editor->asm_obj().symtab);

                qDebug() << NAME << ": panels loaded and console focused — ready for I/O";
            }

            void on_execution_halted(vm_ptr_t rvm, std_word_t pc, bool forced, TextEditor*editor) {
                QString halt_reason = forced ? "forced stop (user requested)" : "halt instruction (program end)";

                qInfo() << NAME << ": execution halted"
                        << "pc =" << format_hex(pc)
                        << "reason =" << halt_reason;

                machine_exec_set_elements(false);
                m_main->action_break_point_continue->setDisabled(true);
                
                if (editor) {
                    editor->clear_all_highlights();
                }
                else {
                    qWarning() << "halted(): NO editor";
                }

                m_console_pptr->on_halted();
                m_memory_pptr->on_halted();
                m_registers_pptr->on_halted();
                m_flags_pptr->on_halted();
                m_symtab_pptr->on_halted();
                m_breakpoints_pptr->on_halted();
            }

            void on_breakpoint(vm_ptr_t rvm, std_word_t addr, TextEditor*editor) {
                qDebug() << NAME << ": breakpoint hit event received"
                         << "address =" << format_hex(addr);
                // enable BP resume 
                m_main->action_break_point_continue->setDisabled(false);

                if (editor) {
                    editor->highlight_breakpoint(addr);   // highlight current breakpoint instruction
                }
            }

            void on_after_instruction(vm_ptr_t vm, std_word_t pc, TextEditor*editor) {
                if (is_debug_mode() && editor) {
                    qDebug() << NAME << ": debug step completed" << "pc =" << format_hex(pc);
                    editor->highlight_addr(pc, TextEditor::MARKER_PC);   // highlight current instruction
                }
            }

            // actions
            void ac_current_export_assemble() {
                auto editor = m_tabs_man_ptr->tab();
                m_machine_man_ptr->export_asm(editor);
            }

            void ac_current_assemble() {
                auto editor = m_tabs_man_ptr->tab();
                m_machine_man_ptr->assemble({editor});
            }

            void ac_current_run() {
                auto editor = m_tabs_man_ptr->tab();
                m_machine_man_ptr->run(editor, is_debug_mode(), settings.get_bool(EXT_ENABLED));
            }

            void ac_current_debug() {
                // switch exec policy
                m_main->action_mode_step_tog->setChecked(true);
                ac_current_run();
            }

            void ac_execution_stop() {
                m_machine_man_ptr->stop();
            }

            void ac_execution_next() {
                m_machine_man_ptr->next();
            }

            void ac_execution_resume() {
                // disable next button
                m_main->action_break_point_continue->setDisabled(true);
                m_machine_man_ptr->breakpoint_resume();
            }

            void machine_exec_set_elements(bool executing) {
                // common actions — disabled while VM is executing
                m_main->action_open_file->setDisabled(executing);
                m_main->action_new_file->setDisabled(executing);
                m_main->action_save->setDisabled(executing);
                m_main->action_save_as->setDisabled(executing);
                m_main->action_assemble->setDisabled(executing);
                m_main->action_mode_step_tog->setDisabled(executing);
                m_main->action_mode_run_tog->setDisabled(executing);
                m_main->action_run->setDisabled(executing);
                m_main->action_debug->setDisabled(executing);

                // stop is only enabled while executing
                m_main->action_stop->setDisabled(!executing);

                // step controls only available in STEP policy
                if (executing) {
                    m_main->action_debug_next->setDisabled(!is_debug_mode());
                }
                // step controls always disabled when not executing
                else {
                    m_main->action_debug_next->setDisabled(true);
                }

                qDebug() << NAME << ": UI actions updated"
                         << (executing ? "(execution active)" : "(idle)");
            }

            bool is_debug_mode() {
                return m_main->action_mode_step_tog->isChecked();
            }
    };
} // namespace lc3kit::ide
