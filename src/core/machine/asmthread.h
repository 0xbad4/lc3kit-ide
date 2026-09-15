#pragma once

#include "utils/common.h"
#include "utils/logger.h"

#include <QQueue>
#include <QMutex>
#include <QBuffer>

#include "core/editor/editor.h"

namespace lc3kit::ide
{
    class AsmThread : public QThread {
        Q_OBJECT

        public:
            inline static const QString NAME = "Assembler";
            
            explicit AsmThread(QObject* parent = nullptr) : QThread(parent) {}

            // returns false if error
            bool assemble(const qassemble_item& item) {
                if (!item.editor) {
                    DTERROR(NAME << ": assemble() called with null editor pointer — ignoring request (no source to assemble)");
                    DLWARN("Assemble called with no editor", NAME);
                    return false;
                }

                DTLOG(NAME << ": queueing assembly job"
                         << "file =" << item.editor->name()
                         << "run_after =" << item.run
                         << "debug =" << item.is_debug);

                { 
                    QMutexLocker l(&m_q_mutex); 
                    m_operations_q.enqueue(item);
                    DTLOG(NAME << ": assembly job queued — queue size =" << m_operations_q.size());
                }

                if (!isRunning()) {
                    DTLOG(NAME << ": assembler thread not running — starting thread");
                    start();
                }

                return true;
            }

            void stop() {
                if (!isRunning()) {
                    DTLOG(NAME << ": stop() called but thread not running — no action needed");
                    return;
                }

                DTLOG(NAME << ": stopping assembler thread");
                QMutexLocker l(&m_q_mutex); 
                quit();
                wait();
                m_operations_q.clear();
                DTLOG(NAME << ": assembler thread stopped — queue cleared");
                emit fstopped();
            }

            const lasm::Asm& assembler() const { return m_asm; }

        signals:
            void assembled(qasm_ctx ctx);
            void aserror(qasm_ctx ctx);
            void fstopped();

        protected:
            QQueue<qassemble_item> m_operations_q;
            QMutex m_q_mutex;
            lasm::Asm m_asm   {};

            bool read_editor(TextEditor* editor, QByteArray& buffer) {
                QBuffer buf(&buffer);

                if (!buf.open(QIODevice::WriteOnly)) {
                    DLERROR("Failed to open buffer for assembly", NAME);
                    return false;
                }

                editor->dump(&buf);
                buf.close();
                return true;
            }
            
            void run() override {
                for (;;) {
                    qassemble_item item;

                    {
                        QMutexLocker l(&m_q_mutex);
                        if (m_operations_q.isEmpty()) {
                            DTLOG(NAME << ": work queue empty — assembler thread exiting");
                            break;
                        }

                        DTLOG(NAME << ": dequeuing assembly job"
                                 << "remaining_in_queue =" << m_operations_q.size());

                        item = m_operations_q.dequeue();
                    }

                    if (!item.editor) {
                        DTWARN(NAME << ": dequeued assembly job but editor pointer is null — skipping job");
                        continue;
                    }

                    DTLOG(NAME << ": starting assembly"
                             << "file =" << item.editor->name()
                             << "ext =" << item.ext);

                    QByteArray bytes;

                    if (!read_editor(item.editor, bytes)) {
                        DTERROR(NAME << ": failed to read source from editor — assembly aborted");
                        continue;
                    }

                    DTLOG(NAME << ": read source code"
                             << "size =" << bytes.size() << "bytes");

                    lasm::source_code src { bytes.constData(), (uint32_t)bytes.size() };
                    m_asm.set_ext_enabled(item.ext);

                    // Assembler resets auto
                    if (m_asm.assemble(src)) {
                        // success
                        DTINFO(NAME << ": assembly succeeded"
                                << "file =" << item.editor->name()
                                << "sections =" << m_asm.sections().size()
                                << "symbols =" << m_asm.sym_table().size());
                        qasm_obj obj { m_asm.sections(), m_asm.sym_table(), m_asm.line_addresses() };
                        emit assembled(qasm_ctx(item, std::move(obj)));
                    }
                    else {
                        // failure
                        DTWARN(NAME << ": assembly failed"
                                   << "file =" << item.editor->name()
                                   << "error_count =" << m_asm.errors().size());
                        DLWARN(QString("Assembly failed for '%1' (%2 error(s))").arg(item.editor->name()).arg(m_asm.errors().size()), NAME);
                        emit aserror(qasm_ctx(item, m_asm.errors()));
                    }
                }
            }
        };
}