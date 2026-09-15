#pragma once

#include "utils/common.h"
#include "dialogs/file.h"
#include "dialogs/ask.h"
#include "core/editor/editor.h"
#include "def_tab.h"

#include <QStackedWidget>

namespace lc3kit::ide
{
    class TabManager : public QObject {
        Q_OBJECT
        
        public:
            inline static const QString NEW_TAB_DEFAULT_NAME = "Untitled";
            inline static const QString NAME = "Editor";

            explicit TabManager(QTabWidget* tptr) : QObject(tptr), tabs_ptr(tptr) {
                setup_tabs();
                setup_te_search();
                setup_hotkeys();
            }

            void open_file() {
                // ask for dialog
                QString chosen = filed::get_open_file(tabs_ptr);

                if (chosen.isEmpty()) {
                    qDebug() << NAME << ": open file dialog cancelled by user";
                    DLWARN("Open file cancelled", NAME);
                    return;
                }

                qInfo() << NAME << ": opening file from disk"
                        << "path =" << chosen;

                new_file_with_path(chosen);
            }

            void new_file() {
                new_file_with_path("");
            }

            void new_file_with_path(const QString& fp) {
                QString filepath = QFileInfo(fp).canonicalFilePath();
                
                // If already open
                if (!fp.isEmpty() && m_open_files_tabs.contains(filepath)) {
                    qDebug() << NAME << ": file already open";
                    tabs_ptr->setCurrentWidget(m_open_files_tabs[filepath]);
                    return;
                }

                qDebug() << NAME << ": creating new editor tab"
                         << "path =" << (filepath.isEmpty() ? "<untitled>" : filepath);

                FileHandler* fh;

                if (fp.isEmpty()) {
                    fh = new FileHandler(this);
                }
                else {
                    fh = new FileHandler(filepath, this);
                }

                if (!fh) {
                    qCritical() << NAME << ": failed to allocate FileHandler"
                                << "path =" << (filepath.isEmpty() ? "<new untitled>" : filepath)
                                << "— tab creation aborted";
                    return;
                }

                TextEditor* new_tab = new TextEditor(fh, is_asm_file(filepath), tabs_ptr);
                new_tab->load();

                connect(new_tab, &TextEditor::content_saved, this, &TabManager::on_content_saved);
                connect(new_tab, &TextEditor::content_changed, this, &TabManager::on_content_changed);
                connect(new_tab, &TextEditor::textChanged, this, &TabManager::on_text_changed);

                int index = tabs_ptr->addTab(new_tab, filepath.isEmpty() ? NEW_TAB_DEFAULT_NAME : new_tab->name());

                qInfo() << NAME << ": new editor tab created and added"
                        << "index =" << index
                        << "file =" << (filepath.isEmpty() ? "<untitled>" : filepath)
                        << "total_tabs =" << tabs_ptr->count();

                tabs_ptr->setCurrentIndex(index);

                // link filepath to tab ptr
                m_open_files_tabs.insert(filepath, tabs_ptr->widget(index));
            }

            void current_save() {
                auto cur = tab();

                if (cur) {
                    cur->save();
                }
            }

            void current_save_as() {
                auto cur = tab();

                if (cur) {
                    cur->save_as();
                }
            }

            void current_undo() {
                auto cur = tab();

                if (cur) {
                    cur->undo();
                }
            }

            void current_redo() {
                auto cur = tab();

                if (cur) {
                    cur->redo();
                }
            }

            void current_find() {
                auto cur = tab();

                // if there is a tab
                if (cur) {
                    if (m_search_ptr->isHidden()) {
                        m_search_ptr->ashow();  // animated show
                        m_search_ptr->init_term(cur->selectedText());
                    }
                    else {
                        m_search_ptr->aclose();
                    }
                }
            }
            
            void current_copy() {
                auto cur = tab();

                if (cur) {
                    cur->copy();
                }
            }
            
            void current_copy_line() {
                auto cur = tab();

                if (cur) {
                    cur->copy_line();
                }
            }

            void current_copy_all() {
                auto cur = tab();

                if (cur) {
                    cur->copy_all();
                }
            }

            void current_copy_path() {
                auto cur = tab();

                if (cur) {
                    cur->copy_path();
                }
            }

            void current_cut() {
                auto cur = tab();

                if (cur) {
                    cur->cut();
                }
            }
            
            void current_paste() {
                auto cur = tab();

                if (cur) {
                    cur->paste();
                }
            }

            void current_line_up() {
                auto cur = tab();

                if (cur) {
                    cur->SendScintilla(QsciScintilla::SCI_MOVESELECTEDLINESUP);
                }
            }

            void current_line_down() {
                auto cur = tab();

                if (cur) {
                    cur->SendScintilla(QsciScintilla::SCI_MOVESELECTEDLINESDOWN);
                }
            }

            void current_line_goto() {
                auto cur = tab();

                if (cur) {
                    cur->e_goto_line();
                }
            }

            void current_line_comment() {
                auto cur = tab();

                if (cur) {
                    cur->toggle_line_comment();
                }
            }

            void current_line_trim_whitespace() {
                auto cur = tab();

                if (cur) {
                    cur->trim_trailing_whitespace();
                }
            }

            void current_clear_breakpoints() {
                auto cur = tab();

                if (cur) {
                    cur->clear_breakpoints();
                }
            }

            void current_toggle_breakpoint() {
                auto cur = tab();

                if (cur) {
                    int line = 0, index = 0;
                    cur->getCursorPosition(&line, &index);
                    cur->toggle_breakpoint(line);
                }
            }

            void current_line_delete() {
                auto cur = tab();

                if (cur) {
                    cur->SendScintilla(QsciScintilla::SCI_LINEDELETE);
                }
            }

            void current_line_duplicate() {
                auto cur = tab();

                if (cur) {
                    cur->SendScintilla(QsciScintilla::SCI_LINEDUPLICATE);
                }
            }

            void current_select_all() {
                auto cur = tab();

                if (cur) {
                    cur->selectAll();
                }
            }

            void current_close() {
                auto cur = tab();
                if (cur) {
                    on_close_tab_requested(tabs_ptr->indexOf(cur));
                }
            }

            void current_treat_as_asm(bool s) {
                auto cur = tab();
                if (cur) {
                    cur->set_is_asm(s);
                }
            }

            void current_show_ws(bool s) {
                auto cur = tab();
                if (cur) {
                    cur->set_show_whitespace(s);
                }
            }

            void current_word_wrap(bool s) {
                auto cur = tab();
                if (cur) {
                    cur->setWrapMode(s ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);
                }
            }

            TextEditor* tab(int index=-1) {
                if (!tabs_ptr) {
                    return nullptr;
                }

                if (!tabs_ptr->count()) {
                    return nullptr;
                }

                return qobject_cast<TextEditor*>(index >= 0 ? tabs_ptr->widget(index) : tabs_ptr->currentWidget());
            }

            void save_all() {
                TextEditor* editor = nullptr;

                for (int i = 0; i < tabs_ptr->count(); i++) {
                    editor = tab(i);

                    if (!editor) {
                        continue;
                    }

                    editor->save();
                }
            }

            bool is_there_unsaved() {
                TextEditor* editor = nullptr;

                for (int i = 0; i < tabs_ptr->count(); i++) {
                    editor = tab(i);

                    if (!editor) {
                        continue;
                    }

                    if (editor->is_changed()) {
                        return true;
                    }
                }

                return false;
            }

            /**
             * @return @c true if operation canceled, @c false otherwise (save | ignore changes) 
             */
            bool ask_to_save() {
                auto ask_res = dialog::ask("Save", "Save changes?", tabs_ptr, true);
                
                if (ask_res == QMessageBox::Cancel) {
                    return true;
                }
                
                if (ask_res == QMessageBox::Yes) {
                    save_all();
                }

                return false;
            }

            void change_editors_theme() {
                TextEditor* editor = nullptr;

                for (int i = 0; i < tabs_ptr->count(); i++) {
                    editor = tab(i);

                    if (!editor) {
                        continue;
                    }

                    editor->update_theme();
                }

                // update text search popup icons
                if (m_search_ptr) {
                    m_search_ptr->setup_icons();
                }

                // default tab icons
                m_default_widget->setup_icons();

            }

        signals:
            void editor_saved(TextEditor*);

        protected:
            QTabWidget*       tabs_ptr = nullptr;
            TextEditorSearch* m_search_ptr = nullptr;
            DefaultTab*       m_default_widget = nullptr;
            QHash<QString, QWidget*> m_open_files_tabs;
            bool m_replacing = false;
            
            void setup_tabs() {
                connect(tabs_ptr, &QTabWidget::tabCloseRequested, this, &TabManager::on_close_tab_requested);
                connect(tabs_ptr, &QTabWidget::currentChanged, this, &TabManager::on_current_tab_changed);
                auto *sw = tabs_ptr->findChild<QStackedWidget*>();
                sw->setFrameShape(QFrame::Shape::NoFrame);
                tabs_ptr->tabBar()->setDrawBase(false);
                setup_default_tab();
            }

            void setup_default_tab() {
                // default tab
                m_default_widget = new DefaultTab(tabs_ptr);
                int index = tabs_ptr->addTab(m_default_widget, "");
                tabs_ptr->tabBar()->setTabVisible(index, false);
                tabs_ptr->setCurrentIndex(index);
            }

            void setup_hotkeys() {
                new QShortcut(QKeySequence::Save, this, [this]() { current_save(); });
                new QShortcut(QKeySequence::SaveAs, this, [this]() { current_save_as(); });
                new QShortcut(QKeySequence::Find, this, [this]() { current_find(); });
                new QShortcut(QKeySequence::FindNext, this, [this]() { on_search_next_requested(); });
                new QShortcut(QKeySequence::FindPrevious, this, [this]() { on_search_previous_requested(); });
                new QShortcut(QKeySequence(Qt::Key::Key_Escape), this, [this]() { on_search_close(); });
            }

            void setup_te_search() {
                if (!m_search_ptr) {
                    m_search_ptr = new TextEditorSearch(tabs_ptr);
                }

                connect(m_search_ptr, &TextEditorSearch::search_text_changed, this, &TabManager::on_search_text_changed);
                connect(m_search_ptr, &TextEditorSearch::next_requested, this, &TabManager::on_search_next_requested);
                connect(m_search_ptr, &TextEditorSearch::previous_requested, this, &TabManager::on_search_previous_requested);
                connect(m_search_ptr, &TextEditorSearch::replace_current_requested, this, &TabManager::on_search_replace_current_requested);
                connect(m_search_ptr, &TextEditorSearch::replace_all_requested, this, &TabManager::on_search_replace_all_requested);
                connect(m_search_ptr, &TextEditorSearch::closed, this, &TabManager::on_search_close);
            }

            void unlink_filepath_tab(QWidget*widget) {
                if (!widget) {
                    return;
                }

                for (auto it = m_open_files_tabs.begin(); it != m_open_files_tabs.end(); ++it) {
                    if (it.value() == widget) {
                        m_open_files_tabs.erase(it);
                        break;
                    }
                }
            }

            void on_search_close() {
                m_search_ptr->close();
                auto editor = tab();

                if (editor) {
                    editor->search_clear();
                }
            }

            void on_current_tab_changed(int index) {
                qDebug() << NAME << ": current tab changed"
                         << "new_index =" << index;

                auto editor = tab(index);
                if (!editor) {
                    qWarning() << NAME << ": tab changed to index" << index
                               << "but no TextEditor widget found — invalid state";
                    return;
                }

                qDebug() << NAME << ": switching to tab"
                         << "file =" << editor->name();

                editor->search_clear();

                if (!m_search_ptr->isHidden()) {
                    int matches = editor->search(m_search_ptr->term());
                    m_search_ptr->total(matches);
                    qDebug() << NAME << ": search results updated for new tab"
                             << "matches =" << matches;
                }
            }
            
            void on_close_tab_requested(int index) {
                qDebug() << NAME << ": tab close requested"
                         << "index =" << index;

                auto editor = tab(index);

                if (!editor) {
                    qWarning() << NAME << ": close requested for tab index" << index
                               << "but no TextEditor found — tab may already be closed";
                    return;
                }

                qDebug() << NAME << ": closing tab"
                         << "file =" << editor->name();

                if (editor->is_assembling() || editor->is_running()) {
                    qWarning() << NAME << ": cannot close tab while busy"
                               << "file =" << editor->name()
                               << "assembling =" << editor->is_assembling()
                               << "running =" << editor->is_running();
                    DLWARN("Cannot close tab while still working (Assembling or Running)", NAME);
                    return;
                }

                if (editor->is_changed()) {
                    qDebug() << NAME << ": tab has unsaved changes — prompting user to save"
                             << "file =" << editor->name();

                    auto ask_res = dialog::ask("Save", "Save changes?", tabs_ptr, true);;

                    if (ask_res == QMessageBox::Cancel) {
                        return;
                    }
                    
                    if (ask_res == QMessageBox::Yes) {
                        // if no path, editor requests it
                        if(!editor->save()) {
                            // if could not save, don't close
                            qWarning() << NAME << ": user chose to save but save failed — tab not closed"
                                       << "file =" << editor->name();
                            return;
                        }
                    }
                }

                qInfo() << NAME << ": closing tab"
                        << "file =" << editor->name()
                        << "index =" << index
                        << "remaining_tabs =" << (tabs_ptr->count() - 1);
                    
                unlink_filepath_tab(tabs_ptr->widget(index));
                tabs_ptr->removeTab(index);
                editor->deleteLater();  // safe: deferred until event loop is idle
            }

            void on_content_saved(const QString& fp) {
                QString filepath = QFileInfo(fp).canonicalFilePath();

                auto* editor = qobject_cast<TextEditor*>(sender());
                
                if (!editor) {
                    return;
                }

                // remove previous if exists (case if save-as)
                unlink_filepath_tab(editor);

                int index = tabs_ptr->indexOf(editor);
                
                if (index == -1) {
                    return;
                }

                // remove the "*" and set the clean filename from the saved path
                tabs_ptr->setTabText(index, editor->name());

                // link new filepath to widget
                m_open_files_tabs.insert(filepath, editor);

                emit editor_saved(editor);
            }

            void on_text_changed() {
                auto* editor = qobject_cast<TextEditor*>(sender());
                if (!editor) return;

                if (!m_replacing && !m_search_ptr->isHidden()) {
                    int matches = editor->search(m_search_ptr->term(), false);
                    m_search_ptr->total(matches);
                }
            }

            void on_content_changed() {
                auto* editor = qobject_cast<TextEditor*>(sender());
                if (!editor) return;

                int index = tabs_ptr->indexOf(editor);
                if (index == -1) return;

                // add "*" prefix only if not already there
                QString current = tabs_ptr->tabText(index);

                if (!current.startsWith('*')) {
                    tabs_ptr->setTabText(index, '*' + current);
                }
            }
    
            void on_search_text_changed(const QString& term) {
                auto editor = tab();

                if (editor) {
                    m_search_ptr->total(editor->search(term));
                }
            }

            void on_search_next_requested() {
                auto editor = tab();

                if (editor) {
                    m_search_ptr->current(editor->search_next());
                }
            }

            void on_search_previous_requested() {
                auto editor = tab();

                if (editor) {
                    m_search_ptr->current(editor->search_previous());
                }
            }

            void on_search_replace_current_requested(const QString& repl) {
                auto editor = tab();

                m_replacing = true;

                if (editor && editor->search_replace(repl)) {
                    m_search_ptr->total(editor->search(m_search_ptr->term()));
                    m_search_ptr->current(editor->search_ctx().current);
                }
                
                m_replacing = false;
            }

            void on_search_replace_all_requested(const QString& repl) {
                auto editor = tab();

                m_replacing = true;
                
                if (editor && editor->search_replace_all(repl)) {
                    m_search_ptr->total(editor->search(m_search_ptr->term()));
                    m_search_ptr->current(editor->search_ctx().current);
                }

                m_replacing = false;
            }   
    };
} // namespace lc3kit::ide
