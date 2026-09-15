#pragma once

#include "lexer.h"
#include "utils/filehand.h"
#include "utils/logger.h"
#include "dialogs/ask.h"
#include "dialogs/text_editor_search.h"
#include <QShortcut>
#include <QMouseEvent>
#include <QBuffer>
#include <QMutex>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QPainter>
#include <QClipboard>
#include <QGuiApplication>
#include "core/machine/asm_ctx.h"

namespace lc3kit::ide
{
    struct qsearch_ctx {
        QString     term;
        QList<uint> results;
        int         current = -1;
    };

    class TextEditor : public QsciScintilla {
        Q_OBJECT

        // breakpoints signals
        signals:
            // a breakpoint was added at this (0-based) line
            void breakpoint_added(int line);
            // a breakpoint was removed from this (0-based) line
            void breakpoint_removed(int line);
            // the file was written to disk at `path`
            void content_saved(const QString&);
            // the buffer went from saved to unsaved (dirty)
            void content_changed();
            // is_asm() changed - fired by set_is_asm() / the context-menu toggle
            void is_asm_changed(bool is_asm);

        protected:
            bool       m_is_asm = true;  // handle non asm files
            bool       m_saved = true;
            bool       m_is_assembling = false;
            bool       m_is_running = false;
            bool       m_whitespace_visible = false;

            QMutex     m_asm_ctx_mutex;

            // Scintilla marker handles for user breakpoints - NOT line numbers.
            QSet<int>  m_bp_handles;
            qsearch_ctx  m_se_ctx;

            // tracks the single active line for "current position" style markers
            // so re-highlighting only ever moves ONE marker
            // instead of nuking every marker of that type - see highlight_line().
            QHash<int,int> m_last_marker_pos;

            // if the PC marker currently sits on top of a line that also has a user
            // breakpoint, that breakpoint's margin dot is hidden (so the two symbols
            // don't overlap in the same margin cell) and its line is recorded here so
            // it can be restored the moment the PC marker moves off it or is cleared.
            int m_bp_hidden_for_pc = -1;

            AsmLexer*   m_lexer     = nullptr;
            TxtLexer*   m_txt_lexer = nullptr;  // used in place of m_lexer when !is_asm() - see apply_asm_mode()
            QsciAPIs*   m_apis      = nullptr;
            FileHandler* fh_ptr     = nullptr;
            qasm_ctx*    m_asm_ctx  = nullptr;

            // auto-complete trigger
            void keyPressEvent(QKeyEvent* event) override {
                QsciScintilla::keyPressEvent(event);

                if (m_is_asm) {
                    // trigger autocomplete after 1 char if word is in progress
                    if (event->key() != Qt::Key_Escape
                        && event->key() != Qt::Key_Return
                        && event->key() != Qt::Key_Space
                        && !event->text().isEmpty())
                    {
                        autoCompleteFromAPIs();
                    }
                    // NOTE: special case
                    // Ctrl + / -> comment/uncomment current line
                    if (event->key() == Qt::Key_Slash && event->modifiers() & Qt::ControlModifier) {
                        toggle_line_comment();
                    }
                }

                if (!event->text().isEmpty() && m_saved) {
                    m_saved = false;
                    emit content_changed();
                }
            }

            // right-click menu - standard edit actions + editor-specific ones
            void contextMenuEvent(QContextMenuEvent* event) override {
                QMenu menu(this);

                QAction* act_undo = menu.addAction("Undo", this, [this]{ undo(); });
                act_undo->setEnabled(isUndoAvailable());
                QAction* act_redo = menu.addAction("Redo", this, [this]{ redo(); });
                act_redo->setEnabled(isRedoAvailable());
                menu.addSeparator();

                QAction* act_cut = menu.addAction("Cut", this, [this]{ cut(); });
                act_cut->setEnabled(hasSelectedText());
                QAction* act_copy = menu.addAction("Copy", this, [this]{ copy(); });
                act_copy->setEnabled(hasSelectedText());
                menu.addAction("Copy Line", this, [this]() { copy_line(); });
                menu.addAction("Copy All", this, [this]() { copy_all(); });
                QAction* act_copy_path = menu.addAction("Copy Path", this, [this](){ copy_path(); });
                act_copy_path->setEnabled(fh_ptr && fh_ptr->has_path());
                menu.addAction("Paste", this, [this]{ paste(); });
                menu.addAction("Select All", this, [this]{ selectAll(); });
                menu.addSeparator();

                menu.addAction("Duplicate Line", this, [this]{ SendScintilla(SCI_LINEDUPLICATE); });
                menu.addAction("Move Line Up\tAlt+Up", this, [this]{ SendScintilla(SCI_MOVESELECTEDLINESUP); });
                menu.addAction("Move Line Down\tAlt+Down", this, [this]{ SendScintilla(SCI_MOVESELECTEDLINESDOWN); });
                menu.addAction("Delete Line\tCtrl+Shift+K", this, [this]{ SendScintilla(SCI_LINEDELETE); });
                menu.addAction("Go to Line...\tCtrl+G", this, &TextEditor::e_goto_line);

                if (m_is_asm) {
                    menu.addAction("Toggle Line Comment\tCtrl+/", this, &TextEditor::toggle_line_comment);

                    int line = lineAt(event->pos());
                    if (line >= 0) {
                        bool has_bp = has_breakpoint(line);
                        menu.addAction(has_bp ? "Remove Breakpoint" : "Add Breakpoint",
                                       this, [this, line]{ toggle_breakpoint(line); });
                    }

                    QAction* act_clear_bp = menu.addAction("Clear Breakpoints", this, [this]{ clear_breakpoints(); });
                    act_clear_bp->setEnabled(has_any_breakpoints());
                }

                menu.addSeparator();

                QAction* act_wrap = menu.addAction("Word Wrap");
                act_wrap->setCheckable(true);
                act_wrap->setChecked(wrapMode() != QsciScintilla::WrapNone);
                connect(act_wrap, &QAction::toggled, this, [this](bool on) {
                    setWrapMode(on ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);
                });

                QAction* act_ws = menu.addAction("Show Whitespace");
                act_ws->setCheckable(true);
                act_ws->setChecked(m_whitespace_visible);
                connect(act_ws, &QAction::toggled, this, &TextEditor::set_show_whitespace);

                menu.addAction("Trim Trailing Whitespace", this, [this]{ trim_trailing_whitespace(); });

                menu.addSeparator();

                QAction* act_asm = menu.addAction("Treat File as Assembly");
                act_asm->setCheckable(true);
                act_asm->setChecked(m_is_asm);
                connect(act_asm, &QAction::toggled, this, &TextEditor::set_is_asm);

                event->accept();
                menu.exec(event->globalPos());
            }

            // help
            // margin click - toggle breakpoint on that line
            void on_margin_clicked(int margin, int line, Qt::KeyboardModifiers) {
                if (margin != MARGIN_BP) {
                    return;
                }
                toggle_breakpoint(line);
            }

            void on_modification_changed(bool changed) {
                m_saved = !changed;
                
                if (changed) {
                    emit content_changed();
                }

                clear_highlight(MARKER_ERROR);
                clearAnnotations();
            }

            void on_text_changed() {
                if (m_asm_ctx) {
                    m_asm_ctx->src.fresh = false;
                }
            }

            void jump_to_search(int idx) {
                if (idx < 0 || idx >= m_se_ctx.results.size()) return;
                int pos = m_se_ctx.results[idx];
                int line, col;
                lineIndexFromPosition(pos, &line, &col);
                setSelection(line, col, line, col + m_se_ctx.term.length());
                ensureLineVisible(line);

                // make the active match visually pop out from the rest
                clearIndicatorRange(0, 0, lines(), lineLength(lines() - 1), IND_SEARCH_CURRENT);
                fillIndicatorRange(line, col, line, col + m_se_ctx.term.length(), IND_SEARCH_CURRENT);
            }

            // deletes the live marker handle (if any) tracking `line`'s breakpoint -
            // does NOT touch m_bp_hidden_for_pc. Returns true if one was found.
            bool delete_bp_handle_at(int line) {
                for (int h : m_bp_handles) {
                    if (markerLine(h) == line) {
                        markerDeleteHandle(h);
                        m_bp_handles.remove(h);
                        return true;
                    }
                }
                return false;
            }

            // resolves a VM address to its source line via the last assemble result.
            // returns -1 if nothing is assembled or the address has no matching line.
            int line_for_addr(std_word_t addr) const {
                if (!is_assembled()) {
                    return -1;
                }

                for (const auto& item : m_asm_ctx->obj().linesaddrs) {
                    if (item.second == addr) {
                        return item.first;
                    }
                }

                return -1;
            }

            // SETUP
            // QSS cannot reach QScintilla (Idk why)
            QString editor_qss() const {
                return QString(
                    "QsciScintilla { border: none; }"
                    "QsciScintilla QAbstractItemView {"
                    "   background-color: %1;"
                    "   color: %2;"
                    "   border: 1px solid %3;"
                    "   outline: none;"
                    "   padding: 2px;"
                    "   selection-background-color: %4;"
                    "   selection-color: %5;"
                    "}"
                    "QsciScintilla QAbstractItemView::item {"
                    "   padding: 3px 6px;"
                    "}"
                    "QsciScintilla QScrollBar:vertical, QsciScintilla QScrollBar:horizontal {"
                    "   background: %6;"
                    "}"
                    "QAbstractScrollArea::corner {"
                    "   background: %7;"
                    "   border: none;"
                    "}"
                )
                .arg(qsspalette.bg_1.name())
                .arg(qsspalette.text_0.name())
                .arg(qsspalette.border.name())
                .arg(qsspalette.bg_3.name())
                .arg(qsspalette.accent_hi.name())
                .arg(edpalette.editor_background.name())
                .arg(edpalette.editor_background.name());
            }

            // editor
            void setup_editor() {
                setFrameShape(QFrame::Shape::NoFrame);
                setLineWidth(0);
                setMidLineWidth(0);
                setContentsMargins(0, 0, 0, 0);

                // tabs default to a long arrow glyph when whitespace is visible - swap
                // to the much subtler strikeout mark instead (1 = SCTD_STRIKEOUT)
                SendScintilla(SCI_SETTABDRAWMODE, 1);

                // end of line
                setEolMode(QsciScintilla::EolUnix);
                setEolVisibility(false);

                // scrolling
                setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
                setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

                // wrap
                setWrapMode(QsciScintilla::WrapNone);

                // signals
                connect(this, &QsciScintilla::marginClicked, this, &TextEditor::on_margin_clicked);
                connect(this, &QsciScintilla::modificationChanged, this, &TextEditor::on_modification_changed);
                connect(this, &QsciScintilla::textChanged, this, &TextEditor::on_text_changed);
            }

            void setup_style() {
                setStyleSheet(editor_qss());
                
                if (viewport()) {
                    viewport()->setStyleSheet("border: none;");
                }

                // caret line - always visible, in every mode, running or not
                setCaretForegroundColor(edpalette.caret_foreground);
                setCaretLineBackgroundColor(edpalette.caret_line_background.lighter(120));
                setCaretLineVisible(true);

                auto sbc = edpalette.selection_background;
                sbc.setAlpha(60);
                setSelectionBackgroundColor(sbc);
                SendScintilla(SCI_SETSELALPHA, sbc.alpha());  // Scintilla's plain SCI_SETSELBACK drops alpha otherwise
                resetSelectionForegroundColor();

                // whitespace
                setWhitespaceForegroundColor(edpalette.margin_foreground);


                // PC - blue right arrow
                markerDefine(QsciScintilla::RightArrow, MARKER_PC);
                setMarkerForegroundColor(edpalette.marker_pc_foreground, MARKER_PC);
                setMarkerBackgroundColor(edpalette.marker_pc_background, MARKER_PC);

                // breakpoint - small custom dot, drawn at a fixed pixel size so it never
                // scales up to the built-in Circle's full line-height size.
                {
                    const int d = 9;
                    QPixmap bp_pixmap(d, d);
                    bp_pixmap.fill(Qt::transparent);
                    QPainter p(&bp_pixmap);
                    p.setRenderHint(QPainter::Antialiasing, true);
                    p.setBrush(edpalette.marker_breakpoint_background);
                    p.setPen(QPen(edpalette.marker_breakpoint_foreground, 1));
                    p.drawEllipse(QRectF(0.5, 0.5, d - 1, d - 1));
                    p.end();
                    markerDefine(bp_pixmap, MARKER_BREAKPOINT);
                }

                // error
                markerDefine(QsciScintilla::Background, MARKER_ERROR);
                setMarkerBackgroundColor(edpalette.marker_error_background, MARKER_ERROR);
                SendScintilla(SCI_MARKERSETALPHA, MARKER_ERROR, 60);

                // current instruction - full-line background shared by plain PC
                // stepping AND a paused breakpoint (see highlight_line()); the margin
                // symbol is what still tells them apart (arrow vs dot)
                markerDefine(QsciScintilla::Background, MARKER_CURRENT);
                setMarkerBackgroundColor(edpalette.indicator_pc_foreground, MARKER_CURRENT);
                SendScintilla(SCI_MARKERSETALPHA, MARKER_CURRENT, 60);

                // indicators
                setIndicatorForegroundColor(edpalette.indicator_search_foreground, IND_SEARCH);
                setIndicatorForegroundColor(edpalette.indicator_search_foreground, IND_SEARCH_CURRENT);
            }

            void setup_margins() {
                // line numbers
                setMarginType(MARGIN_LINES, QsciScintilla::NumberMargin);

                // breakpoint margin - structure/markers always defined; whether it's
                // wide/clickable is decided by apply_asm_mode() so is_asm can toggle live.
                setMarginWidth(MARGIN_BP, 16);
                setMarginType(MARGIN_BP, QsciScintilla::SymbolMargin);
                setMarginMarkerMask(MARGIN_BP, (1 << MARKER_PC) | (1 << MARKER_BREAKPOINT) | (1 << MARKER_ERROR) | (1 << MARKER_CURRENT));
            }

            void setup_annotations() {
                QColor bg = edpalette.marker_error_background;
                bg.setAlpha(100);

                SendScintilla(SCI_STYLESETFORE, STYLE_ERROR_ANNOTATION, edpalette.editor_foreground); // or a dedicated color
                SendScintilla(SCI_STYLESETBACK, STYLE_ERROR_ANNOTATION, bg);
                SendScintilla(SCI_STYLESETFONT, STYLE_ERROR_ANNOTATION, QFont(edpalette.editor_font, edpalette.editor_font_size - 1).family().toUtf8().constData());
                setAnnotationDisplay(QsciScintilla::AnnotationIndented);
            }

            // autocomplete
            void setup_autocomplete() {
                if (!m_lexer) {
                    qCritical() << "Lexer ptr is null, no autocomplete";
                    return;
                }

                m_apis = new QsciAPIs(m_lexer);

                // mnemonics
                for (const auto& m : MNEMONICS) m_apis->add(m);

                // directives
                for (const auto& d : DIRECTIVES)
                    m_apis->add(d);

                // registers
                for (int i = 0; i <= 7; i++) m_apis->add(QString("R%1").arg(i));
                m_apis->add("PC"); m_apis->add("PSR");

                m_apis->prepare();

                setAutoCompletionThreshold(1);      // trigger after 1 character
                setAutoCompletionCaseSensitivity(false);
                setAutoCompletionReplaceWord(true);
                setAutoCompletionUseSingle(QsciScintilla::AcusNever);
                // AutoCompletionSource itself is set by apply_asm_mode() (Acs::AcsAPIs / AcsNone)

                // Scintilla's default word-chars set doesn't include '.', so it never
                // recognized ".ORIG"/".FILL"/etc as a single word to autocomplete
                // against - it only ever saw "ORIG"/"FILL" (no leading dot), which
                // can't match the directive entries in the API list. Add '.' so
                // directives are picked up the same as any other identifier.
                QByteArray word_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.";
                SendScintilla(SCI_SETWORDCHARS, 0.0, word_chars.constData());
            }

            // indicators (search matches + the "stopped at this breakpoint" highlight)
            void setup_indicators() {
                // search - every match: subtle translucent box, drawn under the glyphs
                indicatorDefine(QsciScintilla::IndicatorStyle::FullBoxIndicator, IND_SEARCH);
                SendScintilla(SCI_INDICSETALPHA, IND_SEARCH, 70);
                SendScintilla(SCI_INDICSETOUTLINEALPHA, IND_SEARCH, 0.0);
                SendScintilla(SCI_INDICSETUNDER, IND_SEARCH, 1);

                // search - the active match: same color, much stronger, sharp corners so
                // it's unmistakably different from the rest of the matches
                indicatorDefine(QsciScintilla::IndicatorStyle::StraightBoxIndicator, IND_SEARCH_CURRENT);
                SendScintilla(SCI_INDICSETALPHA, IND_SEARCH_CURRENT, 90);
                SendScintilla(SCI_INDICSETOUTLINEALPHA, IND_SEARCH_CURRENT, 0.0);
                SendScintilla(SCI_INDICSETUNDER, IND_SEARCH_CURRENT, 1);
            }

            void setup_fhand() {
                if (!fh_ptr) {
                    return;
                }

                connect(fh_ptr, &FileHandler::content_saved, this, &TextEditor::on_fh_content_saved);
            }

            // activates/deactivates the asm-only features (lexer, breakpoint margin,
            // autocomplete) based on m_is_asm.
            void apply_asm_mode(bool c=true) {
                // some state clearance
                if (c) {
                    clear_all_highlights();
                    clear_breakpoints();
                    clearAnnotations();
                }

                if (m_is_asm) {
                    if (!m_lexer) {
                        m_lexer = new AsmLexer(this);
                    }
                    setLexer(static_cast<QsciLexer*>(m_lexer));
                }
                else {
                    if (!m_txt_lexer) {
                        m_txt_lexer = new TxtLexer(this);
                    }
                    setLexer(static_cast<QsciLexer*>(m_txt_lexer));
                }

                setMarginSensitivity(MARGIN_BP, m_is_asm);
                setAutoCompletionSource(m_is_asm ? QsciScintilla::AcsAPIs : QsciScintilla::AcsNone);

                // background
                setMarginsBackgroundColor(edpalette.margin_background);
                setMarginsForegroundColor(edpalette.margin_foreground);

                // font fallback for non-lexer regions
                setFont(QFont(edpalette.editor_font, edpalette.editor_font_size));
                setMarginsFont(QFont(edpalette.editor_font, edpalette.editor_font_size));

                setMarginWidth(MARGIN_LINES, "0000000");
                setup_annotations();
            }

            void on_fh_content_saved(const QString& path) {
                m_saved = true;
                emit content_saved(path);
            }

        public:
             // margin and marker indices
            static constexpr int MARGIN_LINES = 0;
            static constexpr int MARGIN_BP    = 1;
            static constexpr int MARKER_PC          = 0;  // current instruction, margin arrow
            static constexpr int MARKER_BREAKPOINT  = 1;  // user-set breakpoint, margin dot
            static constexpr int MARKER_ERROR       = 2;  // assembler error, line background
            static constexpr int MARKER_CURRENT     = 3;  // current-instruction line background - shared by plain PC stepping and a paused breakpoint
            static constexpr int IND_SEARCH         = 0;  // all search matches
            static constexpr int IND_SEARCH_CURRENT = 2;  // active search match
            static constexpr int STYLE_ERROR_ANNOTATION = 20;

            explicit TextEditor(FileHandler*fhptr, bool isasm=true, QWidget* parent = nullptr) : QsciScintilla(parent), m_is_asm(isasm), fh_ptr(fhptr) {
                qDebug() << "TextEditor: constructing editor"
                         << "file =" << (fhptr ? fhptr->filename() : "<none>")
                         << "asm_mode =" << isasm;

                setup_editor();
                setup_margins();
                setup_autocomplete();
                setup_indicators();
                setup_annotations();
                setup_fhand();
                setup_style();

                apply_asm_mode();

                qInfo() << "TextEditor: editor initialized"
                        << "file =" << (fhptr ? fhptr->filename() : "<none>")
                        << "asm_mode =" << isasm
                        << "window_id =" << (qulonglong)this;
            }

            // the file handler backing this editor (path, read/write) - may be null
            FileHandler* filehand() {
                return fh_ptr;
            }

            // true if this file is currently treated as LC-3 assembly (lexer,
            // breakpoints, autocomplete active) - see set_is_asm()
            bool is_asm() const {
                return m_is_asm;
            }

            // switches asm-mode on/off at runtime (lexer, breakpoint margin,
            // autocomplete, default styling) - e.g. wired to the "Treat File as
            // Assembly" menu toggle.
            void set_is_asm(bool asm_mode) {
                if (m_is_asm == asm_mode) return;
                m_is_asm = asm_mode;
                apply_asm_mode();
                emit is_asm_changed(m_is_asm);
            }

            // true if the buffer has no unsaved changes
            bool is_saved() const {
                return m_saved;
            }

            // true if the buffer has unsaved changes - just !is_saved()
            bool is_changed() const {
                return !m_saved;
            }

            // true while an assemble job for this file is queued/running - see assembling()/assembled()
            bool is_assembling() const {
                return m_is_assembling;
            }

            // true while a VM execution session (RUN or STEP) is active - see running()
            bool is_running() const {
                return m_is_running;
            }

            // display name for tabs/titles - the file's name, or "Editor" if unsaved/new
            QString name() const {
                if (!fh_ptr) {
                    return "Editor";
                }

                return QFileInfo(fh_ptr->path()).fileName();
            }
            
            // true if the last assemble() succeeded - false if it failed or never ran
            bool is_assembled() const {
                if (!m_asm_ctx) {
                    return false;
                }

                return m_asm_ctx->ok();
            }

            // the assembled object (sections/symtab/line-address map) from the last
            // successful assemble - only valid when is_assembled() is true
            const qasm_obj& asm_obj() const {
                return m_asm_ctx->obj();
            }

            // the full context (source + result) from the last assemble attempt
            const qasm_ctx& asm_ctx() const {
                return *m_asm_ctx;
            }
            
            // current find/replace state (term, match positions, active index)
            const qsearch_ctx& search_ctx() {
                return m_se_ctx;
            }

            // number of matches for the current search term
            int search_count() const { 
                return m_se_ctx.results.size();
            }

            // clears the visual search highlighting (both "all matches" and "active
            // match" indicator ranges).
            void clear_search_indicators() {
                int last = qMax(lines() - 1, 0);
                clearIndicatorRange(0, 0, lines(), lineLength(last), IND_SEARCH);
                clearIndicatorRange(0, 0, lines(), lineLength(last), IND_SEARCH_CURRENT);
            }

            void update_theme() {
                if (m_lexer) {
                    m_lexer->deleteLater();
                    m_lexer = nullptr;
                }
                if (m_txt_lexer) {
                    m_txt_lexer->deleteLater();
                    m_txt_lexer = nullptr;
                }
                apply_asm_mode(false);
                setup_annotations();
                setup_style();
            }

            // text processing
            // (re)loads the buffer from the file handler's on-disk content and marks
            // it clean - call once after construction, before showing the tab
            void load() {
                if (!fh_ptr) {
                    return;
                }

                setText(fh_ptr->read());

                // move cursor to top
                setModified(false);
                SendScintilla(SCI_GOTOPOS, 0);
            }
    
            // writes the buffer's current text to an already-open QIODevice (UTF-8) - for
            // exporting/copying, independent of the file handler's own save() path
            bool dump(QIODevice* device) const {
                if (!device || !device->isOpen()) {
                    return false;
                }

                QTextStream stream(device);
                stream.setEncoding(QStringConverter::Utf8);
                stream << text();
                return stream.status() == QTextStream::Ok;
            }

            // writes the buffer to its existing path - call on Ctrl+S / a Save action
            bool save() {
                if (!fh_ptr) {
                    qCritical() << "TextEditor::save(): file handler is null - cannot save (internal state error)";
                    DLERROR("Save failed", name());
                    return false;
                }

                qDebug() << "TextEditor::save(): saving file"
                         << "path =" << fh_ptr->path();

                m_saved = fh_ptr->write(text());

                if (m_saved) {
                    qInfo() << "TextEditor::save(): file saved successfully"
                            << "path =" << fh_ptr->path()
                            << "size =" << text().size() << "characters";
                } else {
                    qWarning() << "TextEditor::save(): file save failed"
                               << "path =" << fh_ptr->path();
                }
                setModified(!m_saved);
                set_is_asm(is_asm_file(fh_ptr->path()));
                return m_saved;
            }

            // prompts for a new path and writes the buffer there - call on Save As
            bool save_as() {
                if (!fh_ptr) {
                    qCritical() << "TextEditor::save_as(): file handler is null - cannot save (internal state error)";
                    DLERROR("Save As failed", name());
                    return false;
                }

                qDebug() << "TextEditor::save_as(): opening file chooser dialog";
                
                m_saved = fh_ptr->write_as(text());

                if (m_saved && fh_ptr->has_path()) {
                    qInfo() << "TextEditor::save_as(): file saved with new path"
                            << "path =" << fh_ptr->path();
                } else {
                    qWarning() << "TextEditor::save_as(): save as operation cancelled or failed";
                }
                setModified(!m_saved);
                set_is_asm(is_asm_file(fh_ptr->path()));
                return m_saved;
            }

            // --- editor extras ----
            void set_show_whitespace(bool on) {
                m_whitespace_visible = on;
                setWhitespaceVisibility(on ? QsciScintilla::WsVisible : QsciScintilla::WsInvisible);
            }
            void copy_path() {
                if (fh_ptr) QGuiApplication::clipboard()->setText(fh_ptr->path());
            }

            void copy_all() {
                QGuiApplication::clipboard()->setText(text());
            }

            void copy_line() {
                int line_from, idx_from, line_to, idx_to;

                if (hasSelectedText()) {
                    getSelection(&line_from, &idx_from, &line_to, &idx_to);
                    if (idx_to == 0 && line_to > line_from) line_to--;
                } else {
                    getCursorPosition(&line_from, &idx_from);
                    line_to = line_from;
                }

                QString out;
                for (int l = line_from; l <= line_to; l++) {
                    out += text(l);
                    if (!out.endsWith('\n')) out += '\n';
                }

                QGuiApplication::clipboard()->setText(out);
            }

            // strips trailing spaces/tabs from every line, keeping each line's ending intact
            void trim_trailing_whitespace() {
                for (int l = 0; l < lines(); l++) {
                    QString t = text(l);

                    // work off a copy with the EOL stripped so the trailing-whitespace
                    // scan below can't eat into it
                    if (t.endsWith("\r\n"))                        t.chop(2);
                    else if (t.endsWith('\n') || t.endsWith('\r')) t.chop(1);

                    int end = t.length();
                    while (end > 0 && (t[end - 1] == ' ' || t[end - 1] == '\t')) end--;

                    if (end != t.length()) {
                        setSelection(l, end, l, t.length());
                        replaceSelectedText("");
                    }
                }
            }

            void toggle_line_comment() {
                if (!is_asm()) return;

                int line_from, idx_from, line_to, idx_to;

                if (hasSelectedText()) {
                    getSelection(&line_from, &idx_from, &line_to, &idx_to);
                    if (idx_to == 0 && line_to > line_from) line_to--;  // exclude a trailing empty selected line
                } else {
                    getCursorPosition(&line_from, &idx_from);
                    line_to = line_from;
                }

                // decide add-comment vs remove-comment from the first non-empty line in range
                bool should_comment = true;
                for (int l = line_from; l <= line_to; l++) {
                    QString t = text(l).trimmed();
                    if (t.isEmpty()) continue;
                    should_comment = !t.startsWith(';');
                    break;
                }

                for (int l = line_from; l <= line_to; l++) {
                    QString line_text = text(l);
                    QString trimmed = line_text.trimmed();

                    if (should_comment) {
                        if (trimmed.isEmpty()) continue;
                        setSelection(l, 0, l, 0);
                        replaceSelectedText("; ");
                    } else if (trimmed.startsWith(';')) {
                        int semi = line_text.indexOf(';');
                        int count = 1;
                        if (semi + 1 < line_text.length() && line_text[semi + 1] == ' ') count = 2;
                        setSelection(l, semi, l, semi + count);
                        replaceSelectedText("");
                    }
                }
            }

            void e_goto_line() {
                bool ok = false;
                int cur_line = 0, cur_col = 0;
                getCursorPosition(&cur_line, &cur_col);

                int target = dialog::number(
                    "Go to Line",
                    QString("Line number (1-%1):").arg(lines()),
                    cur_line + 1, 1, lines(), 1, &ok
                );

                if (!ok) return;

                // target is 1-based (as typed by the user); Scintilla lines are 0-based.
                int line = target - 1;
                setCursorPosition(line, 0);
                ensureLineVisible(line);
            }

            // breakpoints
            void toggle_breakpoint(int line) {
                if (has_breakpoint(line)) {
                    remove_breakpoint(line);
                } else {
                    add_breakpoint(line);
                }
            }

            void add_breakpoint(int line) {
                if (m_last_marker_pos.value(MARKER_PC, -1) == line) {
                    // the PC arrow is already sitting on this exact line - keep the
                    // margin overlap-free; the dot reappears once PC moves off it
                    // (see highlight_line()/clear_highlight())
                    m_bp_hidden_for_pc = line;
                } else {
                    m_bp_handles.insert(markerAdd(line, MARKER_BREAKPOINT));
                }

                emit breakpoint_added(line);
            }

            void remove_breakpoint(int line) {
                delete_bp_handle_at(line);  // no-op if it was hidden rather than drawn

                if (m_bp_hidden_for_pc == line) {
                    m_bp_hidden_for_pc = -1;
                }

                emit breakpoint_removed(line);
            }

            void clear_breakpoints() {
                for (int h : m_bp_handles) {
                    markerDeleteHandle(h);
                }
                m_bp_handles.clear();
                m_bp_hidden_for_pc = -1;
            }

            // true if `line` currently has a user breakpoint. Reads live marker state
            // (plus the PC-overlap hidden slot) rather than a cached line number, so
            // it's always correct after edits shift lines around.
            bool has_breakpoint(int line) const {
                if (line == m_bp_hidden_for_pc) return true;
                return markersAtLine(line) & (1 << MARKER_BREAKPOINT);
            }

            bool has_any_breakpoints() const {
                return !m_bp_handles.isEmpty() || m_bp_hidden_for_pc >= 0;
            }

            // machine
            // call once the assemble thread reports back for this file - stores the
            // result and marks error lines (checks ctx.ok() itself, so pass either
            // outcome straight through)
            void assembled(qasm_ctx& ctx) {
                QMutexLocker locker(&m_asm_ctx_mutex);  // unlock at end of scope

                m_is_assembling = false;

                if (m_asm_ctx) {
                    delete m_asm_ctx;
                }

                m_asm_ctx = new qasm_ctx(ctx);
                ctx.src.fresh = true;

                // mark error lines in the editor
                clear_highlight(MARKER_ERROR);
                clearAnnotations();   // wipe the previous run's messages

                if (!ctx.ok()) {
                    for (const auto& err : ctx.errors()) {
                        report_error_at_line(err.pos.line, QString::fromStdString(lasm::err_str(err.type)));
                    }
                }
            }

            void report_error_at_line(int line, const QString& msg) {
                if (line < 0) {
                    return;
                }
                markerAdd(line, MARKER_ERROR);
                annotate(line, msg, STYLE_ERROR_ANNOTATION);
            }

            void report_error_at_addr(std_word_t addr, const QString& msg) {
                int line = line_for_addr(addr);
                report_error_at_line(line, msg);
            }

            // call right before an assemble job for this file is queued - clears old
            // error markers.
            // NOTE: maybe prevent text editing while waiting.
            void assembling() {
                m_is_assembling = true;
                markerDeleteAll(MARKER_ERROR);
                clearAnnotations();
            }

            // marks the editor as running/not-running for a VM execution session.
            void running(bool r=true) {
                m_is_running = r;
            }

            // prompts for a path and writes the last successful assemble's object
            // sections to it - no-op (with a warning) if nothing is assembled yet
            void export_assembled() {
                QMutexLocker locker(&m_asm_ctx_mutex);  // unlock at end of scope

                if (!is_assembled()) {
                    DLWARN("Nothing to export - assemble first", name());
                    return;
                }

                QString path = QFileDialog::getSaveFileName(
                    this,
                    "Export Object File",
                    QFileInfo(fh_ptr->path()).baseName() + ".obj",
                    "LC-3 Object Files (*.obj);;All Files (*)"
                );

                if (path.isEmpty()) return;

                QFile out(path);

                if (!out.open(QIODevice::WriteOnly)) {
                    DLERROR(QString("Cannot write to '%1'").arg(path), name());
                    return;
                }

                out.write(dump_sections(m_asm_ctx->obj().sections));
                
                DLLOG(QString("Exported: %1").arg(path), name());
            }

            // lookup
            // fully resets the search - highlights, term, and result list. For just
            // hiding highlights while keeping the term/results, use
            // clear_search_indicators() instead
            void search_clear() {
                clear_search_indicators();
                m_se_ctx.term.clear();
                m_se_ctx.results.clear();
                m_se_ctx.current   = -1;
            }

            // replaces the currently active search match with `repl` and advances to
            // the next one - false if there's no active search
            bool search_replace(const QString& repl) {
                 if (m_se_ctx.results.isEmpty()) {
                    return false;
                 }

                // replace the currently selected occurrence
                int pos  = m_se_ctx.results[m_se_ctx.current];
                int line, col;

                lineIndexFromPosition(pos, &line, &col);
                setSelection(line, col, line, col + m_se_ctx.term.length());
                replaceSelectedText(repl);

                // offset shift: repl may be longer/shorter than search term
                int delta = repl.length() - m_se_ctx.term.length();

                // update all stored positions after the replaced one
                for (int i = m_se_ctx.current + 1; i < m_se_ctx.results.size(); i++) {
                    m_se_ctx.results[i] += delta;
                }

                // remove the replaced occurrence and re-highlight
                m_se_ctx.results.removeAt(m_se_ctx.current);

                // clamp index and refresh highlights
                if (!m_se_ctx.results.isEmpty()) {
                    m_se_ctx.current = m_se_ctx.current % m_se_ctx.results.size();
                    search(m_se_ctx.term);   // re-run to rebuild indicator ranges
                    jump_to_search(m_se_ctx.current);
                }
                else {
                    // no more occurrences
                    clear_search_indicators();
                    m_se_ctx.current = -1;
                }

                return true;
            }

            // replaces every current search match with `repl` - false if there's no
            // active search
            bool search_replace_all(const QString& repl) {
                if (m_se_ctx.results.isEmpty()) {
                    return false;
                }

                // replace from last to first so positions don't shift under us
                for (int i = m_se_ctx.results.size() - 1; i >= 0; i--) {
                    int pos = m_se_ctx.results[i];
                    int line, col;
                    lineIndexFromPosition(pos, &line, &col);
                    setSelection(line, col, line, col + m_se_ctx.term.length());
                    replaceSelectedText(repl);
                }

                m_se_ctx.results.clear();
                m_se_ctx.current = -1;
                clear_search_indicators();

                return true;
            }

            // finds and highlights every occurrence of `term`, jumps to the first
            // match, and returns the match count (0 clears the search)
            uint search(const QString& term, bool jmp=true) {
                search_clear();

                if (term.isEmpty()) {
                    return 0;
                }

                m_se_ctx.term    = term;

                // find all occurrences
                QString src = text();
                int pos = 0;

                while ((pos = src.indexOf(term, pos, Qt::CaseInsensitive)) != -1) {
                    m_se_ctx.results.append(pos);
                    pos += term.length();
                }

                // highlight all
                clear_search_indicators();

                for (int p : m_se_ctx.results) {
                    int line, col;
                    lineIndexFromPosition(p, &line, &col);
                    fillIndicatorRange(line, col, line, col + term.length(), IND_SEARCH);
                }

                if (!m_se_ctx.results.isEmpty() && jmp) {
                    m_se_ctx.current = 0;
                    jump_to_search(0);
                }

                return search_count();
            }

            // jumps to the next search match, wrapping around - returns its index
            uint search_next() {
                if (m_se_ctx.results.isEmpty()) {
                    return 0;
                }

                m_se_ctx.current = (m_se_ctx.current + 1) % m_se_ctx.results.size();
                jump_to_search(m_se_ctx.current);
                return (uint)m_se_ctx.current;
            }

            // jumps to the previous search match, wrapping around - returns its index
            uint search_previous() {
                if (m_se_ctx.results.isEmpty()) return 0;
                m_se_ctx.current = (m_se_ctx.current - 1 + m_se_ctx.results.size()) % m_se_ctx.results.size();
                jump_to_search(m_se_ctx.current);
                return (uint)m_se_ctx.current;
            }

            // breakpoints
            // the set of (0-based) lines with a user breakpoint - derived live from
            // Scintilla marker handles (see m_bp_handles) so it's always accurate
            // after edits, never a stale snapshot. Returns by value (not a
            // reference like before) since the line numbers only exist at query time.
            QSet<uint> breakpoints_lines() const { 
                QSet<uint> out;

                for (int h : m_bp_handles) {
                    int l = markerLine(h);
                    if (l >= 0) out.insert((uint)l);
                }

                if (m_bp_hidden_for_pc >= 0) {
                    out.insert((uint)m_bp_hidden_for_pc);
                }

                return out;
            }

            // breakpoint lines translated to VM addresses via the last assemble
            // result - empty if nothing is assembled
            QSet<std_word_t> breakpoints_addrs() { 
                if (!is_assembled()) {
                    return {};
                }

                QSet<uint> bp_lines = breakpoints_lines();
                QSet<std_word_t> addresses;

                for (const auto& line : m_asm_ctx->obj().linesaddrs) {
                    if (bp_lines.contains(line.first)) {
                        addresses.insert(line.second);
                    }
                }

                return addresses;
            }

            // markers
            // moves a "current position" style marker (default: MARKER_PC) to `line` -
            // margin symbol, text cursor navigation, AND (only for MARKER_PC) the
            // shared MARKER_CURRENT full-line background. Used both for routine
            // step-by-step positioning (STEP mode, or RUN mode between breakpoints)
            // and - via highlight_breakpoint() - for a paused breakpoint; the two
            // cases look the same except for which margin symbol is showing.
            //
            // Only the single previous instance of this marker is removed - NOT every
            // marker of that type - so this can never wipe out breakpoints even if a
            // caller mistakenly passes MARKER_BREAKPOINT here.
            void highlight_line(int line, int marker=MARKER_PC) {
                auto it = m_last_marker_pos.constFind(marker);
                int prev_line = (it != m_last_marker_pos.constEnd()) ? it.value() : -1;

                if (marker == MARKER_PC && m_bp_hidden_for_pc >= 0 && m_bp_hidden_for_pc != line) {
                    // PC is moving off a line whose breakpoint dot was hidden - restore it
                    m_bp_handles.insert(markerAdd(m_bp_hidden_for_pc, MARKER_BREAKPOINT));
                    m_bp_hidden_for_pc = -1;
                }

                if (prev_line >= 0) {
                    markerDelete(prev_line, marker);
                    if (marker == MARKER_PC) markerDelete(prev_line, MARKER_CURRENT);
                }

                markerAdd(line, marker);
                if (marker == MARKER_PC) markerAdd(line, MARKER_CURRENT);
                m_last_marker_pos[marker] = line;

                if (marker == MARKER_PC && has_breakpoint(line) && m_bp_hidden_for_pc != line) {
                    // avoid two overlapping margin symbols on the same line
                    delete_bp_handle_at(line);
                    m_bp_hidden_for_pc = line;
                }

                setCursorPosition(line, 0);
                ensureLineVisible(line);
            }

            // moves the current-position marker to the source line for `addr` (see
            // highlight_line() for what actually happens visually). No-op if nothing
            // is assembled or the address has no matching line.
            void highlight_addr(std_word_t addr, int marker=MARKER_PC) {
                int line = line_for_addr(addr);
                if (line >= 0) {
                    highlight_line(line, marker);
                }
            }

            // called when execution PAUSES at a user breakpoint (RUN mode only -
            // breakpoints don't apply in STEP mode). Takes a VM address, same as the
            // VM's own breakpoint-hit signal reports - not a line number. Visually
            // identical to highlight_addr() (arrow + shared MARKER_CURRENT
            // background) - kept as its own named entry point so call sites stay
            // self-documenting about *why* the position moved.
            void highlight_breakpoint(std_word_t addr) {
                highlight_addr(addr, MARKER_PC);
            }

            // clears every marker of the given type (default MARKER_PC) - for
            // MARKER_PC this also clears the shared MARKER_CURRENT background and,
            // if it was hiding a breakpoint dot for overlap avoidance, restores that dot
            void clear_highlight(int marker=MARKER_PC) {
                markerDeleteAll(marker);
                m_last_marker_pos.remove(marker);

                if (marker == MARKER_PC) {
                    markerDeleteAll(MARKER_CURRENT);

                    if (m_bp_hidden_for_pc >= 0) {
                        m_bp_handles.insert(markerAdd(m_bp_hidden_for_pc, MARKER_BREAKPOINT));
                        m_bp_hidden_for_pc = -1;
                    }
                }
            }

            // marks every error location from a failed assemble (1-based source lines
            // in `errors`, converted to Scintilla's 0-based lines internally)
            void highlight_errors(const lasm::errors_t& errors) {
                markerDeleteAll(MARKER_ERROR);

                for (const auto& err : errors) {
                    markerAdd(err.pos.line - 1, MARKER_ERROR);  // scintilla is 0-based
                }
            }

            // clears every transient execution/error marker (PC arrow, the shared
            // current-instruction background, error markers) - call this once a
            // run/debug session finishes. User breakpoints are left alone by default;
            // pass keep_breakpoints=false to wipe those too (e.g. on "Stop and Reset").
            void clear_all_highlights(bool keep_breakpoints=true) {
                markerDeleteAll(MARKER_ERROR);
                markerDeleteAll(MARKER_PC);
                markerDeleteAll(MARKER_CURRENT);
                m_last_marker_pos.remove(MARKER_ERROR);
                m_last_marker_pos.remove(MARKER_PC);

                if (m_bp_hidden_for_pc >= 0) {
                    if (keep_breakpoints) {
                        m_bp_handles.insert(markerAdd(m_bp_hidden_for_pc, MARKER_BREAKPOINT));
                    }
                    m_bp_hidden_for_pc = -1;
                }

                if (!keep_breakpoints) {
                    clear_breakpoints();
                }
            }
        };
} // namespace lc3kit::ied