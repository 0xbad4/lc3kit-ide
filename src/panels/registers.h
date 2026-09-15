#pragma once

#include "base.h"

namespace lc3kit::ide
{
    class Registers : public QObject, public BaseController {
        Q_OBJECT

        public:
            explicit Registers(QTreeWidget*tptr) : QObject(tptr), tree_ptr(tptr) {
                setup_tree();
            }

            QString name() {
                return "Registers";
            }

            void load(vm_ptr_t rvm) {
                m_last_changed_item = nullptr;
                tree_ptr->setUpdatesEnabled(false);
                tree_ptr->clear();

                // populate registers
                std_word_t reg_value = 0;
                vm::registers reg = vm::registers::_R_COUNT;

                for (uint8_t i = 0; i < (uint8_t)vm::registers::_R_COUNT; i++) {
                    reg = (vm::registers)i;
                    reg_value = rvm->reg_read(reg);
                    append_row(reg, reg_value);
                }

                // Memory mapped registers
                for (auto it = m_mmio_registers.constBegin(); it != m_mmio_registers.constEnd(); ++it) {
                    append_row(it.key(), it.value(), rvm->mem_read((std_word_t)it.value(), false));
                }

                tree_ptr->setUpdatesEnabled(true);
            }


            void on_register_changed(vm_ptr_t, vm::registers reg, std_word_t nv) {
                tree_ptr->setUpdatesEnabled(false);

                // identify item
                QTreeWidgetItem* item = nullptr;
                bool found = false;

                for (int i = 0; i < tree_ptr->topLevelItemCount(); i++) {
                    item = tree_ptr->topLevelItem(i);

                    if (item_reg(item) == reg) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    DLWARN(QString("Unknown register \"changed\"."), name());
                    return;
                }

                mark_last_changed(m_last_changed_item, item);
                set_row_values(item, reg, nv);
                tree_ptr->setUpdatesEnabled(true);
            }

            void on_memory_changed(vm_ptr_t, std_word_t addr, std_word_t value) {
                if (!is_mmio(addr)) {
                    return;
                }

                // locate item
                QTreeWidgetItem* item = nullptr;
                bool found = false;

                for (int i = 0; i < tree_ptr->topLevelItemCount(); i++) {
                    item = tree_ptr->topLevelItem(i);

                    if (item_addr(item) == addr) {
                        found = true;
                        break;
                    }
                }

                if (!found || !item) {
                    return;
                }

                // update item
                set_row_values(item, vm::registers::_R_COUNT, value, m_mmio_registers.key((vm::mmio)addr));

                // mark as changed
                mark_last_changed(m_last_changed_item, item);
            }

        protected:
            QTreeWidget* tree_ptr = nullptr;
            QTreeWidgetItem* m_last_changed_item = nullptr;
            QMap<QString, vm::mmio> m_mmio_registers = {
                {"KBSR",  vm::mmio::KBSR},
                {"KBDR",  vm::mmio::KBDR},
                {"DSR",   vm::mmio::DSR},
                {"DDR",   vm::mmio::DDR},
                {"MCR",   vm::mmio::MCR}
            };

            bool is_mmio(std_word_t addr) {
                return addr >= static_cast<std_word_t>(vm::mmio::KBSR) &&
                    addr <= static_cast<std_word_t>(vm::mmio::MCR);
            }

            void setup_tree() {
                tree_ptr->setHeaderLabels({"Name", "Hex", "Dec", "Bin"});
                tree_ptr->setRootIsDecorated(false);
            }

            void append_row(vm::registers reg, std_word_t val) {
                auto* item = new QTreeWidgetItem(tree_ptr);

                item->setData(0, Qt::UserRole, (uint8_t)reg);  // store raw reg for lookup

                set_row_values(item, reg, val);
            }

            void append_row(QString name, vm::mmio addr, std_word_t val) {
                auto* item = new QTreeWidgetItem(tree_ptr);
                item->setData(0, Qt::UserRole, (std_word_t)addr);  // store raw addr for lookup
                set_row_values(item, vm::registers::_R_COUNT, val, name);
            }

            void set_row_values(QTreeWidgetItem* item, vm::registers reg, std_word_t val, QString reg_name="") {

                if (reg_name.isEmpty()) {
                    reg_name = "R%1";

                    if ((uint8_t)reg <=7) {
                        reg_name = reg_name.arg((uint8_t)reg);
                    }
                    else if (reg == vm::registers::PC) {
                        reg_name = "PC";
                    }
                    else if (reg == vm::registers::PSR) {
                        reg_name = "PSR";
                    }
                    else {
                        reg_name = "UNKNOWN";
                    }
                }

                item->setText(0, reg_name);
                item->setText(1, format_hex(val));
                item->setText(2, QString::number(val));
                item->setText(3, format_binary(val));
            }

            vm::registers item_reg(QTreeWidgetItem* item) {
                return (vm::registers)item->data(0, Qt::UserRole).toUInt();
            }
            
    };

} // namespace lc3kit::ide
