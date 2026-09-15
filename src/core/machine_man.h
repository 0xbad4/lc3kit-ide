#pragma once

#include "utils/common.h"
#include "dialogs/ask.h"
#include "core/machine/asmthread.h"
#include "core/machine/vmthread.h"


namespace lc3kit::ide
{

    class MachineManager : public QObject {
        Q_OBJECT

        public:
            inline static const QString NAME = "Machine";

            MachineManager(QObject *parent) : QObject(parent) {
                qDebug() << NAME << ": constructing machine manager";
            }

            void on_console_input(char c) {
                if (!m_vm_thread_ptr) {
                    return;
                }

                m_vm_thread_ptr->on_console_input(c);
            }

            void export_asm(TextEditor* editor) {
                if (!editor) {
                    return;
                }

                editor->export_assembled();
            }

            void assemble(const qassemble_item& item) {
                if (!item.editor) {
                    qCritical() << NAME << ": assemble() called with null editor pointer — aborting assembly (no source to assemble)";
                    return;
                }

                setup_asm();

                // stage assembling
                item.editor->assembling();

                // queue assemble
                m_asm_thread_ptr->assemble(item);
            }

            void run(TextEditor*editor, bool is_debug=false, bool ext=false) {
                if (!editor) {
                    qCritical() << NAME << ": run() called with null editor pointer — aborting execution (no program to run)";
                    return;
                }

                setup_vm();
                
                qInfo() << NAME << ": starting VM execution"
                        << "file =" << editor->name()
                        << "mode =" << (is_debug ? "DEBUG (step-by-step)" : "NORMAL (continuous)")
                        << "ext_enabled =" << ext;

                bool f_asm = settings.get_bool(ASM_EVERY_RUN);

                // 1. Never assembled -> always assemble.
                // 2. Already assembled but source changed/not fresh -> assemble only if f_asm is enabled.
                // 3. Already assembled and fresh -> don't assemble.
                if (!editor->is_assembled() || (f_asm && !editor->asm_ctx().src.fresh)) {
                    qDebug() << NAME << ": assembling program before execution";
                    assemble({editor, true, is_debug, true});
                    return;
                }

                if (!prepare(editor, is_debug, ext)) {
                    // failed, abort
                    qWarning() << NAME << ": failed to prepare VM for execution — aborting run";
                    return;
                }

                // track running editor
                m_running_editor = editor;

                // set editor running
                editor->running();

                QString exec_policy = is_debug ? "STEP (step-by-step)" : "RUN (continuous)";

                qInfo() << NAME << ": VM thread" << exec_policy << "policy set — execution beginning now";

                if (is_debug) {
                    m_vm_thread_ptr->prepare_debug();
                    // In debug mode, emit state after first instruction
                    on_after_instruction(m_vm_thread_ptr->vm(), m_vm_thread_ptr->vm()->pc());
                }
                else {
                    m_vm_thread_ptr->start();
                }
            }

            void next() {
                if (m_vm_thread_ptr) {
                    m_vm_thread_ptr->step();
                }
            }

            void breakpoint_resume() {
                if (m_vm_thread_ptr) {
                    if(m_vm_thread_ptr->is_in_breakpoint()) {
                        m_vm_thread_ptr->start();
                    }
                }
            }

            void stop() {
                if (m_vm_thread_ptr) {
                    m_vm_thread_ptr->stop();
                }
            }

            ~MachineManager() {
                if (m_vm_thread_ptr)  {
                    m_vm_thread_ptr->stop(false);  
                    delete m_vm_thread_ptr;
                }
                
                if (m_asm_thread_ptr) {
                    m_asm_thread_ptr->stop(); 
                    delete m_asm_thread_ptr;
                }
            }

        signals:
            void started(vm_ptr_t);
            void reset(vm_ptr_t);

            void execution_started(vm_ptr_t vm, TextEditor*);
            void execution_halted(vm_ptr_t vm, std_word_t pc, bool f, TextEditor*);
            
            void breakpoint(vm_ptr_t vm, std_word_t addr, TextEditor*);
            
            void before_instruction(vm_ptr_t, std_word_t pc);
            void after_instruction(vm_ptr_t, std_word_t pc, TextEditor*);
            
            void after_memory_write(vm_ptr_t, std_word_t address, std_word_t value);
            
            void before_register_write(vm_ptr_t, vm::registers reg, std_word_t old_value, std_word_t new_value);
            void after_register_write(vm_ptr_t, vm::registers reg, std_word_t value);
            
            void before_trap(vm_ptr_t, uint8_t vector);
            void after_trap(vm_ptr_t, uint8_t vector);
            
            void before_interrupt(vm_ptr_t, vm::interrupts intr);
            void after_interrupt(vm_ptr_t, vm::interrupts intr);
            
            void invalid_instruction(vm_ptr_t, std_word_t instruction);
            void invalid_memory_access(vm_ptr_t, std_word_t address, bool is_write);
            
            void console_output(char c);
        
        protected:
            VMThread*  m_vm_thread_ptr  = nullptr;
            AsmThread* m_asm_thread_ptr = nullptr;

            // current running editor
            TextEditor* m_running_editor = nullptr;

            // hook wiring
            // hooks fire on the VM thread — emit signals which Qt delivers
            // to connected slots on the UI thread via QueuedConnection

            void wire_hooks(vm_ptr_t vm) {
                auto& h  = vm->hooks();

                h.on_start = [this](vm::VM&vm) {
                    DLLOG("Started", NAME);
                    on_execution_started(&vm);
                };

                h.on_reset = [this](vm::VM&vm) {
                    emit reset(&vm);
                };

                h.before_instruction = [this](vm::VM&vm, std_word_t pc) {
                    emit before_instruction(&vm, pc);
                };

                h.after_instruction = [this](vm::VM&vm, std_word_t pc) {
                    on_after_instruction(&vm, pc);
                };

                h.after_memory_write = [this](vm::VM&vm, std_word_t addr, std_word_t val) {
                    emit after_memory_write(&vm, addr, val);
                };

                h.before_register_write = [this](vm::VM&vm, vm::registers reg, std_word_t old_v, std_word_t new_v) {
                    emit before_register_write(&vm, reg, old_v, new_v);
                };

                h.after_register_write = [this](vm::VM&vm, vm::registers reg, std_word_t val) {
                    emit after_register_write(&vm, reg, val);
                };

                h.on_breakpoint = [this](vm::VM&vm, std_word_t addr) -> bool {
                    qDebug() << NAME << ": VM breakpoint hit at" << format_hex(addr);
                    emit on_breakpoint(&vm, addr);
                    return false;  // pause — let the thread stop, UI calls step/run to resume
                };

                h.before_trap = [this](vm::VM&vm, uint8_t vec) {
                    qDebug() << NAME << ": before trap — vector =" << format_hex((uint)vec);
                    emit before_trap(&vm, vec);
                };

                h.after_trap = [this](vm::VM&vm, uint8_t vec) {
                    qDebug() << NAME << ": after trap — vector =" << format_hex((uint)vec);
                    emit after_trap(&vm, vec);
                };

                h.on_invalid_instruction = [this](vm::VM&vm, std_word_t instr) {
                    qCritical() << NAME << ": invalid instruction encountered"
                                << "instruction =" << format_hex(instr)
                                << "pc =" << format_hex(vm.pc());
                    emit invalid_instruction(&vm, instr);
                };

                h.on_invalid_memory_access = [this](vm::VM&vm, std_word_t addr, bool is_write) {
                    qCritical() << NAME << ": invalid memory access"
                                << "address =" << format_hex(addr)
                                << "access_type =" << (is_write ? "write" : "read")
                                << "pc =" << format_hex(vm.pc());
                    emit invalid_memory_access(&vm, addr, is_write);
                };

                h.on_halt = [this](vm::VM&vm, std_word_t pc, bool f) {
                    QString reason = f ? "forced stop" : "halt instruction";
                    qInfo() << NAME << ": VM halted"
                            << "pc =" << format_hex(pc)
                            << "reason =" << reason;

                    on_execution_halted(&vm, pc, f);
                };
            }

            // machine setup
            void setup_vm() {
                if (m_vm_thread_ptr) {
                    m_vm_thread_ptr->stop();
                    delete m_vm_thread_ptr;
                }

                m_vm_thread_ptr = new VMThread(this);

                // wire hooks
                wire_hooks(m_vm_thread_ptr->vm());

                // set display callback
                m_vm_thread_ptr->display().set_callback([this](char c, void*) { 
                    emit console_output(c);
                });
            }

            void setup_asm() {
                if (m_asm_thread_ptr) {
                    m_asm_thread_ptr->stop();
                    delete m_asm_thread_ptr;
                }
                m_asm_thread_ptr = new AsmThread(this);

                connect(m_asm_thread_ptr, &AsmThread::assembled, this, &MachineManager::on_assembler_finished, Qt::ConnectionType::QueuedConnection);
                connect(m_asm_thread_ptr, &AsmThread::aserror, this, &MachineManager::on_assembler_finished, Qt::ConnectionType::QueuedConnection);
            }

            std_word_t pick_origin_section(const qasm_obj& obj, bool*ok) {
                if (obj.sections.size() < 2) {
                    *ok = true;
                    return obj.sections[0].origin;
                } 

                QMap<QString, std_word_t> secs;

                auto sym = [obj](std_word_t o) {
                    for (const auto& s : obj.symtab) {
                        if (s.second == o) {
                            return s.first;
                        }
                    }
                    return str_t();
                };
                auto line = [obj](std_word_t o) {
                    for (const auto& s : obj.linesaddrs) {
                        if (s.second == o) {
                            return s.first;
                        }
                    }
                    return uint(0);
                };

                // PROG @ x3000 : (line 6)
                for (const auto& sec : obj.sections) {
                    secs.insert(
                        QString("%1 @ %2  (line %3)")
                            .arg(QString::fromStdString(sym(sec.origin)))  // label
                            .arg(format_hex(sec.origin))  // addr
                            .arg(line(sec.origin)), // line
                        sec.origin
                    );
                }

                QString orig_str = dialog::pick(
                    "Select Origin",
                    "Multiple origins detected. Choose one to start from:",
                    secs.keys(),
                    ok
                );

                if (secs.contains(orig_str)) {
                    return secs[orig_str];
                }
                else {
                    *ok = false;
                    return 0;
                }
            }

            // machine preparing
            bool prepare(TextEditor* editor, bool is_debug, bool en_ext) {

                qDebug() << NAME << ": preparing VM"
                         << "exec_policy =" << (is_debug ? "STEP" : "RUN")
                         << "ext_enabled =" << en_ext;

                m_vm_thread_ptr->prepare(is_debug ? vm::exec_policy::STEP : vm::exec_policy::RUN, en_ext);

                // load assembled program from editor context
                const qasm_obj& obj = editor->asm_obj();

                // if there multiple section make user pick which one
                bool ok;
                std_word_t origin = pick_origin_section(obj, &ok);

                if (!ok) {
                    qDebug() << NAME << ": no origin picked, - aborting execution";
                    return false;
                }

                qDebug() << NAME << ": loading assembled program"
                         << "source_file =" << editor->name()
                         << "sections =" << obj.sections.size();

                if (!m_vm_thread_ptr->load(obj.sections)) {
                    qCritical() << NAME << ": VM rejected assembled program — aborting execution";
                    DLERROR("Failed to load program into VM, check previous logs", NAME);
                    return false;
                }

                // set origin
                // if only one section, its set automatically
                if (obj.sections.size() > 1 && !m_vm_thread_ptr->set_origin(origin)) {
                    return false;
                }

                qInfo() << NAME << ": program loaded into VM @PC=" << format_hex(m_vm_thread_ptr->vm()->pc()) << "— applying breakpoints";

                // set breakpoints
                set_breakpoints(editor, is_debug);

                return true;
            }

            void set_breakpoints(TextEditor* editor, bool dbg) {
                auto bpts = editor->breakpoints_addrs();

                if (dbg) {
                    DLLOG("Breakpoints are not allowed in STEP mode, skipping breakpoint registration", NAME);
                    return;
                }

                qDebug() << NAME << ": setting breakpoints"
                         << "count =" << bpts.size();

                for (auto addr : bpts) {
                    qDebug() << NAME << ": registering breakpoint"
                             << "address =" << format_hex(addr);
                    m_vm_thread_ptr->vm()->add_break_point(addr);
                }

                if (bpts.size() > 0) {
                    qInfo() << NAME << ": registered" << bpts.size() << "breakpoint(s)";
                } else {
                    qDebug() << NAME << ": no breakpoints to register";
                }
            }

            void on_assembler_finished(qasm_ctx ctx) {
                if (!ctx.src.editor) {
                    qCritical() << NAME << ": assembler callback received but editor pointer is null — assembly context cannot be applied (internal error)";
                    return;
                }

                qDebug() << NAME << ": assembler finished — processing results"
                         << "file =" << ctx.src.editor->name();

                if (!ctx.ok()) {
                    qWarning() << NAME << ": assembly failed"
                               << "file =" << ctx.src.editor->name()
                               << "error_count =" << ctx.errors().size();
                    for (const auto err : ctx.errors()) {
                        DLERROR(QString("%1 %2:%3").arg(lasm::err_str(err.type)).arg(err.pos.line+1).arg(err.pos.col+1), AsmThread::NAME);
                    }
                }
                else {
                    qInfo() << NAME << ": assembly succeeded"
                            << "file =" << ctx.src.editor->name()
                            << "sections =" << ctx.obj().sections.size()
                            << "symbols =" << ctx.obj().symtab.size();
                    DLLOG("Assembled successfully", AsmThread::NAME);
                }

                ctx.src.editor->assembled(ctx);

                if (ctx.ok() && ctx.src.run) {
                    qDebug() << NAME << ": auto-run triggered after successful assembly";
                    run(ctx.src.editor, ctx.src.is_debug, ctx.src.ext);
                }
            }

            void on_execution_halted(vm_ptr_t vm, std_word_t pc, bool f) {
                QString stop_reason = f ? "forced stop" : "halt instruction";
                qInfo() << NAME << ": VM execution halted"
                        << "pc =" << format_hex(pc)
                        << "reason =" << stop_reason;

                emit execution_halted(vm, pc, f, m_running_editor);

                if (m_running_editor) {
                    // report errors if any
                    if (!vm->ok()) {
                        m_running_editor->report_error_at_addr(
                            pc,
                            QString::fromStdString(vm::err_str(vm->get_last_error()))
                        );
                    }

                    m_running_editor->running(false);
                    m_running_editor = nullptr;
                }
            }

            void on_execution_started(vm_ptr_t vm) {
                qInfo() << NAME << ": VM execution started"
                        << "initial_pc =" << format_hex(vm->pc());
                emit execution_started(vm, m_running_editor);
            }

            void on_breakpoint(vm_ptr_t vm, std_word_t addr) {
                qInfo() << NAME << ": breakpoint hit"
                        << "address =" << format_hex(addr);
                emit breakpoint(vm, addr, m_running_editor);
            }

            void on_after_instruction(vm_ptr_t vm, std_word_t pc) {
                qDebug() << NAME << ": instruction executed"
                         << "pc =" << format_hex(pc);
                emit after_instruction(vm, pc, m_running_editor);
            }

    };
    
} // namespace lc3kit::ide
