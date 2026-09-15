#pragma once
#include "utils/common.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWindow>
#include <QMouseEvent>
#include <QActionGroup>
#include <QToolButton>
#include <QKeySequence>


namespace lc3kit::ide
{
    class DragMenuBar : public QMenuBar {
        Q_OBJECT

        public:
            // ---- File ----
            QAction* action_new     = nullptr;
            QAction* action_open    = nullptr;
            QAction* action_save    = nullptr;
            QAction* action_save_as = nullptr;
            QAction* action_close   = nullptr;
            QAction* action_quit    = nullptr;

            // ---- Edit ----
            QAction* action_undo            = nullptr;
            QAction* action_redo            = nullptr;
            QAction* action_cut             = nullptr;
            QAction* action_paste           = nullptr;
            QAction* action_select_all      = nullptr;
            QAction* action_find            = nullptr;
            QAction* action_toggle_comment  = nullptr;
            QAction* action_trim_whitespace = nullptr;
            QAction* action_open_settings   = nullptr;

            // Edit > Copy
            QAction* action_copy_selection = nullptr;
            QAction* action_copy_line      = nullptr;
            QAction* action_copy_all       = nullptr;
            QAction* action_copy_path      = nullptr;

            // Edit > Line
            QAction* action_duplicate_line = nullptr;
            QAction* action_move_up        = nullptr;
            QAction* action_move_down      = nullptr;
            QAction* action_delete_line    = nullptr;
            QAction* action_go_to_line     = nullptr;

            // ---- Run ----
            QAction* action_assemble          = nullptr;
            QAction* action_export_assembled  = nullptr;
            QAction* action_run               = nullptr;
            QAction* action_debug             = nullptr;
            QAction* action_step              = nullptr;
            QAction* action_resume            = nullptr;
            QAction* action_stop              = nullptr;
            QAction* action_toggle_breakpoint = nullptr;
            QAction* action_clear_breakpoints = nullptr;

            // ---- View ----
            QMenu* menu_view = nullptr;

            // ---- Help ----
            QMenu*   menu_examples     = nullptr;
            QAction* action_documentation = nullptr;
            QAction* action_source_code   = nullptr;
            QAction* action_about         = nullptr;

            DragMenuBar(QMainWindow* par) : QMenuBar(par) {
                setup_menus();
                setup_corner_buttons(par);
            }

        protected:
            void setup_menus() {
                setup_file_menu();
                setup_edit_menu();
                setup_run_menu();
                setup_view_menu();
                setup_help_menu();

                setNativeMenuBar(false);
            }

            void setup_file_menu() {
                QMenu* menu_file = addMenu("File");

                action_new = menu_file->addAction("New");
                action_new->setShortcut(QKeySequence::New);

                action_open = menu_file->addAction("Open");
                action_open->setShortcut(QKeySequence::Open);

                menu_file->addSeparator();

                action_save = menu_file->addAction("Save");
                action_save->setShortcut(QKeySequence::Save);

                action_save_as = menu_file->addAction("Save As");
                action_save_as->setShortcut(QKeySequence::SaveAs);

                menu_file->addSeparator();

                action_close = menu_file->addAction("Close");
                action_close->setShortcut(QKeySequence::Close);

                menu_file->addSeparator();

                action_quit = menu_file->addAction("Quit");
                action_quit->setShortcut(QKeySequence::Quit);
            }

            void setup_edit_menu() {
                QMenu* menu_edit = addMenu("Edit");

                action_undo = menu_edit->addAction("Undo");
                action_undo->setShortcut(QKeySequence::Undo);

                action_redo = menu_edit->addAction("Redo");
                action_redo->setShortcut(QKeySequence::Redo);

                menu_edit->addSeparator();

                action_cut = menu_edit->addAction("Cut");
                action_cut->setShortcut(QKeySequence::Cut);
                
                QMenu* menu_copy = menu_edit->addMenu("Copy");

                action_copy_selection = menu_copy->addAction("Copy Selection");
                action_copy_selection->setShortcut(QKeySequence::Copy);

                action_copy_line = menu_copy->addAction("Copy Line");
                action_copy_all  = menu_copy->addAction("Copy All");
                action_copy_path = menu_copy->addAction("Copy Path");

                action_paste = menu_edit->addAction("Paste");
                action_paste->setShortcut(QKeySequence::Paste);

                action_select_all = menu_edit->addAction("Select All");
                action_select_all->setShortcut(QKeySequence::SelectAll);

                action_find = menu_edit->addAction("Find");
                action_find->setShortcut(QKeySequence::Find);

                menu_edit->addSeparator();

                QMenu* menu_line = menu_edit->addMenu("Line");

                action_duplicate_line = menu_line->addAction("Duplicate");

                action_move_up = menu_line->addAction("Move Up");
                action_move_up->setShortcut(QKeySequence("Alt+Up"));

                action_move_down = menu_line->addAction("Move Down");
                action_move_down->setShortcut(QKeySequence("Alt+Down"));

                action_delete_line = menu_line->addAction("Delete");
                action_delete_line->setShortcut(QKeySequence("Ctrl+Shift+K"));

                action_go_to_line = menu_line->addAction("Go To");
                action_go_to_line->setShortcut(QKeySequence("Ctrl+G"));

                menu_line->addSeparator();

                action_toggle_comment = menu_line->addAction("Toggle Comment");
                action_toggle_comment->setShortcut(QKeySequence("Ctrl+/"));

                menu_edit->addSeparator();
                
                action_trim_whitespace = menu_edit->addAction("Trim Trailing Whitespace");
                
                menu_edit->addSeparator();
                
                action_open_settings = menu_edit->addAction("Settings");
                action_open_settings->setShortcut(QKeySequence("Ctrl+Alt+S"));
            }

            void setup_run_menu() {
                QMenu* menu_run = addMenu("Run");

                action_assemble = menu_run->addAction("Assemble");
                action_assemble->setShortcut(QKeySequence("Ctrl+B"));

                action_export_assembled = menu_run->addAction("Export Assembled...");

                menu_run->addSeparator();

                action_run = menu_run->addAction("Run");
                action_run->setShortcut(QKeySequence("F5"));

                action_debug = menu_run->addAction("Debug");
                action_debug->setShortcut(QKeySequence("F6"));

                action_step = menu_run->addAction("Step");
                action_step->setShortcut(QKeySequence("F10"));

                action_resume = menu_run->addAction("Resume");
                action_resume->setShortcut(QKeySequence("F8"));

                action_stop = menu_run->addAction("Stop");
                action_stop->setShortcut(QKeySequence("Shift+F5"));

                menu_run->addSeparator();

                action_toggle_breakpoint = menu_run->addAction("Toggle Breakpoint");
                action_toggle_breakpoint->setShortcut(QKeySequence("F9"));

                action_clear_breakpoints = menu_run->addAction("Clear Breakpoints");

                menu_run->addSeparator();
            }

            void setup_view_menu() {
                menu_view = addMenu("View");
            }

            void setup_help_menu() {
                QMenu* menu_help = addMenu("Help");

                menu_examples = menu_help->addMenu("Examples");
                // left empty here on purpose — whoever owns the builtin example list
                // (probably main_window.h) should addAction() one entry per example
                // into menu_examples and connect it to whatever opens/loads it

                menu_help->addSeparator();

                action_documentation = menu_help->addAction("Documentation");
                action_source_code   = menu_help->addAction("Source Code");

                menu_help->addSeparator();

                action_about = menu_help->addAction("About");
            }

            void setup_corner_buttons(QMainWindow* par) {
                auto *corner = new QWidget(this);
                auto *layout = new QHBoxLayout(corner);
                layout->setContentsMargins(0, 0, 0, 0);
                layout->setSpacing(0);

                auto *btn_min   = new QToolButton(corner);
                auto *btn_max   = new QToolButton(corner);
                auto *btn_close = new QToolButton(corner);

                btn_min->setIcon(ICON("win-minimize"));
                btn_max->setIcon(ICON("win-restore"));
                btn_close->setIcon(ICON("win-close"));

                btn_min->setIconSize(QSize(20, 20));
                btn_max->setIconSize(QSize(20, 20));
                btn_close->setIconSize(QSize(20, 20));

                btn_min->setObjectName("titlebar_min");
                btn_max->setObjectName("titlebar_max");
                btn_close->setObjectName("titlebar_close");

                layout->addWidget(btn_min);
                layout->addWidget(btn_max);
                layout->addWidget(btn_close);

                setCornerWidget(corner, Qt::TopRightCorner);

                connect(btn_min, &QToolButton::clicked, par, &QMainWindow::showMinimized);
                connect(btn_close, &QToolButton::clicked, par, &QMainWindow::close);
                connect(btn_max, &QToolButton::clicked, this, [par]() { par->isMaximized() ? par->showNormal() : par->showMaximized(); });
            }

            void mousePressEvent(QMouseEvent *e) override {
                if (e->button() == Qt::LeftButton && !actionAt(e->pos())) {
                    if (QWindow *handle = window()->windowHandle()) {
                        handle->startSystemMove();
                    }
                    return;
                }
                QMenuBar::mousePressEvent(e);
            }

            void mouseDoubleClickEvent(QMouseEvent *e) override {
                if (!actionAt(e->pos())) {
                    auto *win = window();
                    win->isMaximized() ? win->showNormal() : win->showMaximized();
                }
                QMenuBar::mouseDoubleClickEvent(e);
            }
    };
    
} // namespace lc3kit::ide