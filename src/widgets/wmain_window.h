/********************************************************************************
** Form generated from reading UI file 'main-windowaqfmtU.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_2D_WINDOWAQFMTU_H
#define MAIN_2D_WINDOWAQFMTU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_assemble;
    QAction *action_run;
    QAction *action_stop;
    QAction *action_debug_next;
    QAction *action_mode_run_tog;
    QAction *action_mode_step_tog;
    QAction *action_break_point_continue;
    QAction *action_open_file;
    QAction *action_save_as;
    QAction *action_save;
    QAction *action_debug;
    QAction *action_new_file;
    QAction *action_show_breakpoints;
    QAction *action_show_console;
    QAction *action_show_flags;
    QAction *action_show_logs;
    QAction *action_show_memory;
    QAction *action_show_settings;
    QAction *action_show_symtab;
    QAction *action_show_registers;
    QAction *action_undo;
    QAction *action_redo;
    QAction *action_cut;
    QAction *action_copy;
    QAction *action_paste;
    QAction *action_find;
    QAction *action_assemble_export;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *body_frame;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *text_editors_tab;
    QDockWidget *console_dockw;
    QWidget *console_dockw_body;
    QVBoxLayout *verticalLayout_5;
    QDockWidget *registers_dockw;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_8;
    QTreeWidget *registers_tree;
    QDockWidget *logs_dockw;
    QWidget *dockWidgetContents_10;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *logs_tree;
    QDockWidget *memory_dockw;
    QWidget *dockWidgetContents_11;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *memory_tree;
    QDockWidget *symtab_dockw;
    QWidget *dockWidgetContents_14;
    QVBoxLayout *verticalLayout_6;
    QTreeWidget *symtab_tree;
    QStatusBar *statusbar;
    QDockWidget *flags_dockw;
    QWidget *flags_dockw_body;
    QVBoxLayout *verticalLayout_16;
    QDockWidget *settings_dockw;
    QWidget *settings_dockw_body;
    QVBoxLayout *verticalLayout_7;
    QDockWidget *breakpoints_dockw;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_9;
    QTreeWidget *breakpoints_tree;
    QToolBar *panelsbar;
    QToolBar *texteditbar;
    QToolBar *toolbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1220, 869);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        action_assemble = new QAction(MainWindow);
        action_assemble->setObjectName("action_assemble");
        action_run = new QAction(MainWindow);
        action_run->setObjectName("action_run");
        action_run->setMenuRole(QAction::MenuRole::NoRole);
        action_stop = new QAction(MainWindow);
        action_stop->setObjectName("action_stop");
        action_stop->setMenuRole(QAction::MenuRole::NoRole);
        action_debug_next = new QAction(MainWindow);
        action_debug_next->setObjectName("action_debug_next");
        action_debug_next->setMenuRole(QAction::MenuRole::NoRole);
        action_mode_run_tog = new QAction(MainWindow);
        action_mode_run_tog->setObjectName("action_mode_run_tog");
        action_mode_run_tog->setCheckable(true);
        action_mode_run_tog->setChecked(true);
        action_mode_run_tog->setMenuRole(QAction::MenuRole::NoRole);
        action_mode_step_tog = new QAction(MainWindow);
        action_mode_step_tog->setObjectName("action_mode_step_tog");
        action_mode_step_tog->setCheckable(true);
        action_mode_step_tog->setShortcutContext(Qt::ShortcutContext::WidgetShortcut);
        action_mode_step_tog->setMenuRole(QAction::MenuRole::NoRole);
        action_break_point_continue = new QAction(MainWindow);
        action_break_point_continue->setObjectName("action_break_point_continue");
        action_break_point_continue->setMenuRole(QAction::MenuRole::NoRole);
        action_open_file = new QAction(MainWindow);
        action_open_file->setObjectName("action_open_file");
        action_open_file->setMenuRole(QAction::MenuRole::NoRole);
        action_save_as = new QAction(MainWindow);
        action_save_as->setObjectName("action_save_as");
        action_save_as->setMenuRole(QAction::MenuRole::NoRole);
        action_save = new QAction(MainWindow);
        action_save->setObjectName("action_save");
        action_save->setMenuRole(QAction::MenuRole::NoRole);
        action_debug = new QAction(MainWindow);
        action_debug->setObjectName("action_debug");
        action_debug->setMenuRole(QAction::MenuRole::NoRole);
        action_new_file = new QAction(MainWindow);
        action_new_file->setObjectName("action_new_file");
        action_new_file->setMenuRole(QAction::MenuRole::NoRole);
        action_show_breakpoints = new QAction(MainWindow);
        action_show_breakpoints->setObjectName("action_show_breakpoints");
        action_show_breakpoints->setCheckable(true);
        action_show_breakpoints->setMenuRole(QAction::MenuRole::NoRole);
        action_show_console = new QAction(MainWindow);
        action_show_console->setObjectName("action_show_console");
        action_show_console->setCheckable(true);
        action_show_console->setMenuRole(QAction::MenuRole::NoRole);
        action_show_flags = new QAction(MainWindow);
        action_show_flags->setObjectName("action_show_flags");
        action_show_flags->setCheckable(true);
        action_show_flags->setMenuRole(QAction::MenuRole::NoRole);
        action_show_logs = new QAction(MainWindow);
        action_show_logs->setObjectName("action_show_logs");
        action_show_logs->setCheckable(true);
        action_show_logs->setMenuRole(QAction::MenuRole::NoRole);
        action_show_memory = new QAction(MainWindow);
        action_show_memory->setObjectName("action_show_memory");
        action_show_memory->setCheckable(true);
        action_show_memory->setMenuRole(QAction::MenuRole::NoRole);
        action_show_settings = new QAction(MainWindow);
        action_show_settings->setObjectName("action_show_settings");
        action_show_settings->setCheckable(true);
        action_show_settings->setMenuRole(QAction::MenuRole::NoRole);
        action_show_symtab = new QAction(MainWindow);
        action_show_symtab->setObjectName("action_show_symtab");
        action_show_symtab->setCheckable(true);
        action_show_symtab->setMenuRole(QAction::MenuRole::NoRole);
        action_show_registers = new QAction(MainWindow);
        action_show_registers->setObjectName("action_show_registers");
        action_show_registers->setCheckable(true);
        action_show_registers->setMenuRole(QAction::MenuRole::NoRole);
        action_undo = new QAction(MainWindow);
        action_undo->setObjectName("action_undo");
        action_undo->setMenuRole(QAction::MenuRole::NoRole);
        action_redo = new QAction(MainWindow);
        action_redo->setObjectName("action_redo");
        action_redo->setMenuRole(QAction::MenuRole::NoRole);
        action_cut = new QAction(MainWindow);
        action_cut->setObjectName("action_cut");
        action_cut->setMenuRole(QAction::MenuRole::NoRole);
        action_copy = new QAction(MainWindow);
        action_copy->setObjectName("action_copy");
        action_copy->setMenuRole(QAction::MenuRole::NoRole);
        action_paste = new QAction(MainWindow);
        action_paste->setObjectName("action_paste");
        action_paste->setMenuRole(QAction::MenuRole::NoRole);
        action_find = new QAction(MainWindow);
        action_find->setObjectName("action_find");
        action_find->setMenuRole(QAction::MenuRole::NoRole);
        action_assemble_export = new QAction(MainWindow);
        action_assemble_export->setObjectName("action_assemble_export");
        action_assemble_export->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        body_frame = new QFrame(centralwidget);
        body_frame->setObjectName("body_frame");
        body_frame->setFrameShape(QFrame::Shape::NoFrame);
        body_frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(body_frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        text_editors_tab = new QTabWidget(body_frame);
        text_editors_tab->setObjectName("text_editors_tab");
        text_editors_tab->setElideMode(Qt::TextElideMode::ElideRight);
        text_editors_tab->setUsesScrollButtons(false);
        text_editors_tab->setDocumentMode(false);
        text_editors_tab->setTabsClosable(true);
        text_editors_tab->setMovable(true);
        text_editors_tab->setTabBarAutoHide(false);

        verticalLayout_2->addWidget(text_editors_tab);


        verticalLayout->addWidget(body_frame);

        MainWindow->setCentralWidget(centralwidget);
        console_dockw = new QDockWidget(MainWindow);
        console_dockw->setObjectName("console_dockw");
        console_dockw->setFloating(false);
        console_dockw->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea);
        console_dockw_body = new QWidget();
        console_dockw_body->setObjectName("console_dockw_body");
        verticalLayout_5 = new QVBoxLayout(console_dockw_body);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        console_dockw->setWidget(console_dockw_body);
        MainWindow->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, console_dockw);
        registers_dockw = new QDockWidget(MainWindow);
        registers_dockw->setObjectName("registers_dockw");
        registers_dockw->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea|Qt::DockWidgetArea::RightDockWidgetArea);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName("dockWidgetContents_5");
        verticalLayout_8 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        registers_tree = new QTreeWidget(dockWidgetContents_5);
        registers_tree->setObjectName("registers_tree");
        registers_tree->setFrameShape(QFrame::Shape::NoFrame);
        registers_tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        registers_tree->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        registers_tree->setIndentation(0);
        registers_tree->header()->setDefaultSectionSize(80);

        verticalLayout_8->addWidget(registers_tree);

        registers_dockw->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, registers_dockw);
        logs_dockw = new QDockWidget(MainWindow);
        logs_dockw->setObjectName("logs_dockw");
        dockWidgetContents_10 = new QWidget();
        dockWidgetContents_10->setObjectName("dockWidgetContents_10");
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_10);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        logs_tree = new QTreeWidget(dockWidgetContents_10);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        logs_tree->setHeaderItem(__qtreewidgetitem);
        logs_tree->setObjectName("logs_tree");
        logs_tree->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        logs_tree->setFrameShape(QFrame::Shape::NoFrame);
        logs_tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        logs_tree->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        logs_tree->setIndentation(0);

        verticalLayout_4->addWidget(logs_tree);

        logs_dockw->setWidget(dockWidgetContents_10);
        MainWindow->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, logs_dockw);
        memory_dockw = new QDockWidget(MainWindow);
        memory_dockw->setObjectName("memory_dockw");
        dockWidgetContents_11 = new QWidget();
        dockWidgetContents_11->setObjectName("dockWidgetContents_11");
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_11);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        memory_tree = new QTreeWidget(dockWidgetContents_11);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        memory_tree->setHeaderItem(__qtreewidgetitem1);
        memory_tree->setObjectName("memory_tree");
        memory_tree->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        memory_tree->setFrameShape(QFrame::Shape::NoFrame);
        memory_tree->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        memory_tree->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        memory_tree->setIndentation(0);

        verticalLayout_3->addWidget(memory_tree);

        memory_dockw->setWidget(dockWidgetContents_11);
        MainWindow->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, memory_dockw);
        symtab_dockw = new QDockWidget(MainWindow);
        symtab_dockw->setObjectName("symtab_dockw");
        symtab_dockw->setStyleSheet(QString::fromUtf8("Sym Table"));
        dockWidgetContents_14 = new QWidget();
        dockWidgetContents_14->setObjectName("dockWidgetContents_14");
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_14);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        symtab_tree = new QTreeWidget(dockWidgetContents_14);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QString::fromUtf8("1"));
        symtab_tree->setHeaderItem(__qtreewidgetitem2);
        symtab_tree->setObjectName("symtab_tree");
        symtab_tree->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        symtab_tree->setFrameShape(QFrame::Shape::NoFrame);
        symtab_tree->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        symtab_tree->setIndentation(0);
        symtab_tree->setItemsExpandable(false);
        symtab_tree->header()->setDefaultSectionSize(100);

        verticalLayout_6->addWidget(symtab_tree);

        symtab_dockw->setWidget(dockWidgetContents_14);
        MainWindow->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, symtab_dockw);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        flags_dockw = new QDockWidget(MainWindow);
        flags_dockw->setObjectName("flags_dockw");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(flags_dockw->sizePolicy().hasHeightForWidth());
        flags_dockw->setSizePolicy(sizePolicy);
        flags_dockw->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea|Qt::DockWidgetArea::LeftDockWidgetArea|Qt::DockWidgetArea::RightDockWidgetArea);
        flags_dockw_body = new QWidget();
        flags_dockw_body->setObjectName("flags_dockw_body");
        verticalLayout_16 = new QVBoxLayout(flags_dockw_body);
        verticalLayout_16->setSpacing(0);
        verticalLayout_16->setObjectName("verticalLayout_16");
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        flags_dockw->setWidget(flags_dockw_body);
        MainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, flags_dockw);
        settings_dockw = new QDockWidget(MainWindow);
        settings_dockw->setObjectName("settings_dockw");
        settings_dockw->setFloating(false);
        settings_dockw->setFeatures(QDockWidget::DockWidgetFeature::DockWidgetClosable|QDockWidget::DockWidgetFeature::DockWidgetFloatable|QDockWidget::DockWidgetFeature::DockWidgetMovable);
        settings_dockw->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea|Qt::DockWidgetArea::LeftDockWidgetArea|Qt::DockWidgetArea::RightDockWidgetArea);
        settings_dockw_body = new QWidget();
        settings_dockw_body->setObjectName("settings_dockw_body");
        verticalLayout_7 = new QVBoxLayout(settings_dockw_body);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        settings_dockw->setWidget(settings_dockw_body);
        MainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, settings_dockw);
        breakpoints_dockw = new QDockWidget(MainWindow);
        breakpoints_dockw->setObjectName("breakpoints_dockw");
        breakpoints_dockw->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea|Qt::DockWidgetArea::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout_9 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        breakpoints_tree = new QTreeWidget(dockWidgetContents);
        breakpoints_tree->setObjectName("breakpoints_tree");
        breakpoints_tree->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        breakpoints_tree->setFrameShape(QFrame::Shape::NoFrame);
        breakpoints_tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        breakpoints_tree->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        breakpoints_tree->setIndentation(0);
        breakpoints_tree->header()->setDefaultSectionSize(150);

        verticalLayout_9->addWidget(breakpoints_tree);

        breakpoints_dockw->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, breakpoints_dockw);
        panelsbar = new QToolBar(MainWindow);
        panelsbar->setObjectName("panelsbar");
        panelsbar->setIconSize(QSize(20, 20));
        MainWindow->addToolBar(Qt::ToolBarArea::BottomToolBarArea, panelsbar);
        texteditbar = new QToolBar(MainWindow);
        texteditbar->setObjectName("texteditbar");
        texteditbar->setIconSize(QSize(18, 18));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, texteditbar);
        toolbar = new QToolBar(MainWindow);
        toolbar->setObjectName("toolbar");
        toolbar->setAllowedAreas(Qt::ToolBarArea::BottomToolBarArea|Qt::ToolBarArea::TopToolBarArea);
        toolbar->setIconSize(QSize(18, 18));
        toolbar->setFloatable(true);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbar);

        panelsbar->addAction(action_show_registers);
        panelsbar->addAction(action_show_flags);
        panelsbar->addAction(action_show_breakpoints);
        panelsbar->addSeparator();
        panelsbar->addAction(action_show_memory);
        panelsbar->addAction(action_show_symtab);
        panelsbar->addSeparator();
        panelsbar->addAction(action_show_logs);
        panelsbar->addAction(action_show_console);
        panelsbar->addSeparator();
        panelsbar->addAction(action_show_settings);
        texteditbar->addAction(action_copy);
        texteditbar->addAction(action_cut);
        texteditbar->addAction(action_paste);
        texteditbar->addSeparator();
        texteditbar->addAction(action_undo);
        texteditbar->addAction(action_redo);
        texteditbar->addSeparator();
        texteditbar->addAction(action_find);
        toolbar->addAction(action_open_file);
        toolbar->addAction(action_new_file);
        toolbar->addAction(action_save);
        toolbar->addAction(action_save_as);
        toolbar->addSeparator();
        toolbar->addAction(action_assemble);
        toolbar->addAction(action_assemble_export);
        toolbar->addSeparator();
        toolbar->addAction(action_run);
        toolbar->addAction(action_debug);
        toolbar->addSeparator();
        toolbar->addAction(action_stop);
        toolbar->addAction(action_debug_next);
        toolbar->addAction(action_break_point_continue);
        toolbar->addSeparator();
        toolbar->addAction(action_mode_run_tog);
        toolbar->addAction(action_mode_step_tog);

        retranslateUi(MainWindow);

        text_editors_tab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_assemble->setText(QString());
#if QT_CONFIG(tooltip)
        action_assemble->setToolTip(QCoreApplication::translate("MainWindow", "Assemble", nullptr));
#endif // QT_CONFIG(tooltip)
        action_run->setText(QString());
#if QT_CONFIG(tooltip)
        action_run->setToolTip(QCoreApplication::translate("MainWindow", "Run", nullptr));
#endif // QT_CONFIG(tooltip)
        action_stop->setText(QString());
#if QT_CONFIG(tooltip)
        action_stop->setToolTip(QCoreApplication::translate("MainWindow", "Stop", nullptr));
#endif // QT_CONFIG(tooltip)
        action_debug_next->setText(QString());
#if QT_CONFIG(tooltip)
        action_debug_next->setToolTip(QCoreApplication::translate("MainWindow", "Next (STEP mode)", nullptr));
#endif // QT_CONFIG(tooltip)
        action_mode_run_tog->setText(QCoreApplication::translate("MainWindow", "RUN", nullptr));
        action_mode_run_tog->setProperty("type", QVariant(QCoreApplication::translate("MainWindow", "exec-mode", nullptr)));
        action_mode_step_tog->setText(QCoreApplication::translate("MainWindow", "STEP", nullptr));
        action_mode_step_tog->setProperty("type", QVariant(QCoreApplication::translate("MainWindow", "exec-mode", nullptr)));
        action_break_point_continue->setText(QString());
#if QT_CONFIG(tooltip)
        action_break_point_continue->setToolTip(QCoreApplication::translate("MainWindow", "Resume execution (breakpoints)", nullptr));
#endif // QT_CONFIG(tooltip)
        action_open_file->setText(QString());
#if QT_CONFIG(tooltip)
        action_open_file->setToolTip(QCoreApplication::translate("MainWindow", "Open File", nullptr));
#endif // QT_CONFIG(tooltip)
        action_save_as->setText(QString());
#if QT_CONFIG(tooltip)
        action_save_as->setToolTip(QCoreApplication::translate("MainWindow", "Save As", nullptr));
#endif // QT_CONFIG(tooltip)
        action_save->setText(QString());
#if QT_CONFIG(tooltip)
        action_save->setToolTip(QCoreApplication::translate("MainWindow", "Save", nullptr));
#endif // QT_CONFIG(tooltip)
        action_debug->setText(QString());
#if QT_CONFIG(tooltip)
        action_debug->setToolTip(QCoreApplication::translate("MainWindow", "Debug", nullptr));
#endif // QT_CONFIG(tooltip)
        action_new_file->setText(QString());
#if QT_CONFIG(tooltip)
        action_new_file->setToolTip(QCoreApplication::translate("MainWindow", "New File", nullptr));
#endif // QT_CONFIG(tooltip)
        action_show_breakpoints->setText(QString());
#if QT_CONFIG(tooltip)
        action_show_breakpoints->setToolTip(QCoreApplication::translate("MainWindow", "Breakpoints", nullptr));
#endif // QT_CONFIG(tooltip)
        action_show_console->setText(QString());
#if QT_CONFIG(tooltip)
        action_show_console->setToolTip(QCoreApplication::translate("MainWindow", "Console", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        action_show_flags->setToolTip(QCoreApplication::translate("MainWindow", "Flags", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        action_show_logs->setToolTip(QCoreApplication::translate("MainWindow", "Logs", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        action_show_memory->setToolTip(QCoreApplication::translate("MainWindow", "Memory", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        action_show_settings->setToolTip(QCoreApplication::translate("MainWindow", "Settings", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        action_show_symtab->setToolTip(QCoreApplication::translate("MainWindow", "Symbole Table", nullptr));
#endif // QT_CONFIG(tooltip)
        action_show_registers->setText(QString());
        action_undo->setText(QString());
#if QT_CONFIG(tooltip)
        action_undo->setToolTip(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#endif // QT_CONFIG(tooltip)
        action_redo->setText(QString());
#if QT_CONFIG(tooltip)
        action_redo->setToolTip(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#endif // QT_CONFIG(tooltip)
        action_cut->setText(QString());
#if QT_CONFIG(tooltip)
        action_cut->setToolTip(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#endif // QT_CONFIG(tooltip)
        action_copy->setText(QString());
#if QT_CONFIG(tooltip)
        action_copy->setToolTip(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#endif // QT_CONFIG(tooltip)
        action_paste->setText(QString());
#if QT_CONFIG(tooltip)
        action_paste->setToolTip(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#endif // QT_CONFIG(tooltip)
        action_find->setText(QString());
#if QT_CONFIG(tooltip)
        action_find->setToolTip(QCoreApplication::translate("MainWindow", "Find", nullptr));
#endif // QT_CONFIG(tooltip)
        action_assemble_export->setText(QString());
#if QT_CONFIG(tooltip)
        action_assemble_export->setToolTip(QCoreApplication::translate("MainWindow", "Export .obj", nullptr));
#endif // QT_CONFIG(tooltip)
        console_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Console", nullptr));
        registers_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Registers", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = registers_tree->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Value", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Register", nullptr));
        logs_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Logs", nullptr));
        memory_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Memory", nullptr));
        symtab_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Sym Table", nullptr));
        flags_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Flags", nullptr));
        settings_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        breakpoints_dockw->setWindowTitle(QCoreApplication::translate("MainWindow", "Breakpoints", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = breakpoints_tree->headerItem();
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Addr", nullptr));
        panelsbar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        texteditbar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolbar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_2D_WINDOWAQFMTU_H
