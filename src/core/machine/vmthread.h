#pragma once
#include <QThread>
#include <functional>
#include "utils/common.h"
#include "utils/logger.h"
#include "utils/settings.h"


namespace lc3kit::ide
{
    class VMThread : public QThread {
        Q_OBJECT

        public:
            inline static const QString NAME = "VM-Thread";

            explicit VMThread(QObject* parent = nullptr) : QThread(parent), m_vm() {
                m_vm.set_hw_display(&m_display);
                m_vm.set_hw_keyboard(&m_keyboard);
            }

            // prepare VM for new execution, reset
            void prepare(vm::exec_policy policy, bool ext) {
                m_vm.reset();
                m_vm.set_exec_policy(policy);
                m_vm.set_boot_mode(vm::boot_mode::BUILTIN_OS);
                m_vm.set_ext_enabled(ext);
            }

            bool set_origin(std_word_t origin) {
                DTLOG(NAME << ": setting vm execution origin @PC = " << format_hex(origin));
                m_vm.set_origin(origin);

                if (!m_vm.ok()) {
                    DLERROR(QString(vm::err_str(m_vm.get_last_error())), NAME);
                    return false;
                }

                DLLOG(QString("VM origin set to %1").arg(format_hex(origin)), NAME);
                return true;
            }

            bool load(const lasm::sections_t& sections) {
                for (const auto& section : sections) {
                    if (!load(export_section(section))) {
                        return false;
                    }

                    DTLOG(NAME << ": section with size = " << section.words.size() << "loaded @" << format_hex(section.origin));
                }

                return true;
            }

            bool load(const QByteArray& bytes) {
                // copy content into a std::istringstream for vm.load()
                std::istringstream stream(str_t(bytes.constData(), bytes.size()));

                return load_(stream);
            }

            void prepare_debug() {
                if (m_vm.get_exec_policy() == vm::exec_policy::STEP) {
                    // STEP policy: first call to exec() arms the machine without executing any instruction.
                    DTLOG(NAME << ": executing in STEP policy - arming machine for first instruction (no execution yet)");
                    m_vm.run();
                }
            }

            bool is_in_breakpoint() {
                return m_vm.is_paused_on_breakpoint() && !isRunning();
            }

            void step() {
                if (m_vm.get_exec_policy() != vm::exec_policy::STEP) {
                    DTWARN(NAME << ": step() called but execution policy is not STEP - ignoring step request");
                    DLWARN("Step ignored: execution policy is not STEP", NAME);
                    return;
                }

                DTLOG(NAME << ": executing single step" << "pc =" << format_hex(m_vm.pc()));
                start();
            }

            void stop(bool log=true) {
                // running normally OR paused on breakpoint (thread not working) OR in step mode (thread not working)
                if (isRunning() || m_vm.is_paused_on_breakpoint() || m_vm.is_running()) {
                    m_vm.stop();
                    wait();
                    if (log) {
                        DTWARN(NAME << ": stop() VM stopped");
                        DLWARN("VM stop requested and honored", NAME);
                    }
                }
                else {
                    if (log) {
                        DTWARN(NAME << ": stop() VM not running");
                        DLWARN("VM stop requested but nothing is running", NAME);
                    }
                }
            }

            vm_ptr_t vm() {
                return &m_vm;
            }

            vm::Display& display() {
                return m_display;
            }

            void on_console_input(char c) {
                auto err = m_keyboard.emit_char(c);

                if (err != vm::error_type::NO_ERROR) {
                    DLERROR(vm::err_str(err), NAME);
                }
            }

            ~VMThread() {
                if (isRunning()) {
                    DTWARN(NAME << ": destructor called while VM thread still running - waiting for thread to stop");
                    wait();
                    DTLOG(NAME << ": VM thread stopped cleanly");
                } else {
                    DTLOG(NAME << ": VM thread already stopped - clean destruction");
                }
            }

        protected:
            vm::VM           m_vm;
            vm::Display      m_display;
            vm::Keyboard     m_keyboard;

            bool load_(std::istream& stream) {
                if (isRunning()) {
                    DLWARN("VM still running", NAME);
                    return false;
                }

                m_vm.load(stream);

                if (!m_vm.ok()) {
                    DLERROR(QString(vm::err_str(m_vm.get_last_error())), NAME);
                    return false;
                }
                
                return true;
            }

            void run() override {
                std_word_t pc = 0;

                if (m_vm.get_exec_policy() == vm::exec_policy::RUN) {
                    m_vm.run();
                    pc = m_vm.pc();
                }
                else {
                    pc = m_vm.step();
                }

                if (!m_vm.is_paused_on_breakpoint()) {
                    // check for errors after run() returns
                    DTLOG("execution finished");
    
                    if (!m_vm.ok()) {
                        DLERROR(QString("@PC=%1 %2").arg(format_hex(pc)).arg(vm::err_str(m_vm.get_last_error())), NAME);
                        DTWARN("@PC=" << format_hex(pc) << " " << vm::err_str(m_vm.get_last_error()));
                    }
                }
                else {
                    DTLOG("execution paused on breakpoint at PC=" << format_hex(pc));
                    DLLOG(QString("Execution paused on breakpoint at %1").arg(format_hex(pc)), NAME);
                }
            }
        };
};
