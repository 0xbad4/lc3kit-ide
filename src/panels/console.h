#pragma once

#include "base.h"
#include <QPaintEvent>
#include <QPainter>
#include <QClipboard>
#include <QMenu>
#include <QAction>

namespace lc3kit::ide
{
    class Console : public QPlainTextEdit, public BaseController {
        Q_OBJECT

        public:
            explicit Console(QWidget*wptr) : QPlainTextEdit(wptr), parentw_ptr(wptr) {
                setup_widget();
            }

            QString name() {
                return "Console";
            }

            void load(vm_ptr_t) {
                clear();
            }

            void on_before_trap(vm_ptr_t, uint8_t tv) {
                if (is_io(tv)) {
                    m_in_io = true;
                    update();
                }
            }

            void on_after_trap(vm_ptr_t, uint8_t tv) {
                if (is_io(tv)) {
                    m_in_io = false;
                    update();
                }
            }

            void on_halted() {
                m_in_io = false;
                update();
            }

            void on_console_output(char c) {
                if (c == '\n') {
                    appendPlainText(QString());   // QTextEdit::append adds a new paragraph
                    return;
                }

                if (c == '\b') {
                    // move cursor back one and delete
                    QTextCursor cursor = textCursor();
                    cursor.deletePreviousChar();
                    setTextCursor(cursor);
                    return;
                }

                // insert at current cursor position
                auto printable = printable_char(c);

                if (!printable.isEmpty()) {
                    QTextCursor cursor = textCursor();
                    cursor.movePosition(QTextCursor::End);
                    cursor.insertText(printable);
                    setTextCursor(cursor);
                    ensureCursorVisible();
                }
            }

        signals:
            void run_requested();
            void debug_requested();
            void console_input(char c);

        protected:
            QWidget* parentw_ptr = nullptr;
            bool m_in_io = false;
            QMenu *menu = nullptr;

            void keyPressEvent(QKeyEvent *event) {
                if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                    emit console_input(10);
                    event->ignore();
                    return;
                }

                if (event->key() == Qt::Key_Backspace) {
                    emit console_input('\b');
                    event->ignore();
                    return;
                }

                if (event->text().isEmpty()) {
                    event->ignore(); 
                    return; 
                }
                
                auto printable = printable_char(event->text().at(0).toLatin1());
                
                if (!printable.isEmpty()) {
                    char c = printable.at(0).toLatin1();

                    if (c != 0) {
                        emit console_input(c);
                        event->accept();
                        return;
                    }
                }

                event->ignore();
            }

            void paintEvent(QPaintEvent *event) {
                QPlainTextEdit::paintEvent(event);

                if (!hasFocus())
                    return;

                QPainter painter(viewport());

                QTextCursor cursor = textCursor();
                QRect rect = cursorRect(cursor);

                // Character-width block cursor
                QFontMetrics fm(font());
                int width = fm.horizontalAdvance(QLatin1Char('M'));

                QRect cursorRect(
                    rect.left(),
                    rect.top(),
                    width,
                    rect.height()
                );

                painter.fillRect(cursorRect, m_in_io ? qsspalette.accent : qsspalette.text_0);

                // Redraw the character underneath in the background color
                painter.setPen(m_in_io ? qsspalette.accent : qsspalette.text_0);
                painter.drawText(cursorRect, Qt::AlignLeft | Qt::AlignVCenter, cursor.document()->characterAt(cursor.position()));
            }

            bool is_io(uint8_t tv) {
                vm::trap_vectors tvect = (vm::trap_vectors)tv;
                return tvect != vm::trap_vectors::HALT;
            }

            void on_context_menu_requested(const QPoint& pos) {
                menu->exec(mapToGlobal(pos));
            }

            void setup_context_menu() {
                menu = new QMenu(this);    

                QAction* act_select_all = menu->addAction("Select All", this, [this]{ selectAll(); });
                act_select_all->setEnabled(!document()->isEmpty());

                QAction* act_copy = menu->addAction("Copy", this, [this]{ copy(); });
                act_copy->setEnabled(textCursor().hasSelection());

                menu->addSeparator();

                menu->addAction("Run", this, [this]{ emit run_requested(); });
                menu->addAction("Debug", this, [this]{ emit debug_requested(); });

                menu->addSeparator();

                menu->addAction("Clear", this, [this]{ if (!m_in_io) clear(); });

                setContextMenuPolicy(Qt::CustomContextMenu);
                connect(this, &QWidget::customContextMenuRequested, this, &Console::on_context_menu_requested);
            }

            void setup_widget() {
                qDebug() << name() << ": setting up console widget";

                if (parentw_ptr->layout()) {
                    parentw_ptr->layout()->addWidget(this);
                    qDebug() << name() << ": console added to parent layout";
                }
                else {
                    qCritical() << name() << ": parent widget has no layout - panel will not be visible (internal state error)";
                    DLERROR("parent widget has no layout", name());
                    return;
                }

                setFrameShape(QFrame::Shape::NoFrame);
                setReadOnly(true);
                setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
                setCursorWidth(fontMetrics().averageCharWidth());
                setup_context_menu();
                qInfo() << name() << ": panel initialized and ready for output";
            }
    };

} // namespace lc3kit::ide
