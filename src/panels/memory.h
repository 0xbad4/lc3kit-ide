#pragma once

#include "base.h"

namespace lc3kit::ide
{
    class MemoryView : public QObject, public BaseController {
        Q_OBJECT

        const QString NAME = "Memory";

        public:
            explicit MemoryView(QTreeWidget*tptr) : QObject(tptr), tree_ptr(tptr) { 
                setup_tree();
            }

            void on_memory_changed(vm_ptr_t rvm, std_word_t addr, std_word_t value) {
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

                if (!found) {
                    DLWARN(QString("Address changed not loaded @ x%1").arg(addr, 4, 16, QChar('0')).toUpper(), NAME);
                    return;
                }

                // get value from memory, compare to value from args
                std_word_t memory_value = rvm->mem_read(addr);

                // log any inconsistency
                if (!is_mmio(addr) && memory_value != value) {
                    DLERROR(QString("Reported changes are inconsistent with the current @ x%1!").arg(addr, 4, 16, QChar('0')).toUpper(), NAME);
                    return;
                }

                // mark as changed
                mark_last_changed(m_last_changed_item, item);

                // update item
                set_row_values(item, addr, value);
            }

            void on_memory_violation(vm_ptr_t, std_word_t addr, bool is_write) {
                DLERROR(
                    QString("Memory violation: %1 @ x%2")
                        .arg(is_write ? "write" : "read")
                        .arg(addr, 4, 16, QChar('0')).toUpper(),
                    NAME
                );
            }

            QString name() {
                return "Memory";
            }

            // explicit load (when program first loaded to memory)
            void load(vm_ptr_t rvm) {
                tree_ptr->setUpdatesEnabled(false);
                tree_ptr->clear();
                m_last_changed_item = nullptr;

                bool populate_all = settings.get_bool(MEMORY_POPULATE_ALL);

                if (populate_all) {
                    // full 64KB address space
                    for (uint32_t addr = 0; addr <= 0xFFFF; addr++) {
                        std_word_t val = rvm->mem_read((std_word_t)addr);
                        append_row(addr, val);
                    }

                    DLLOG("Memory populated: full 64KB", NAME);
                }

                else {
                    // programs only: from origin to origin + used size
                    for (const auto& section : rvm->sections()) {
                        for (std_word_t addr = section.origin; addr < (std_word_t)(section.origin + section.size); addr++) {
                            std_word_t val = rvm->mem_read(addr);
                            append_row(addr, val);
                        }

                        DLLOG(
                            QString("Memory populated: x%1 - x%2 (%3 words)")
                                .arg(section.origin, 4, 16, QChar('0')).toUpper()
                                .arg((std_word_t)(section.origin + section.size - 1), 4, 16, QChar('0')).toUpper()
                                .arg(section.size),
                            NAME
                        );
                    }

                    // load Memory Mapped Registers
                    std_word_t addr = (std_word_t)vm::mmio::KBSR; 

                    for (;addr <= (std_word_t)vm::mmio::MCR; addr += 2) {
                        append_row(addr, rvm->mem_read(addr));
                    }
                }

                tree_ptr->setUpdatesEnabled(true);
            }

        protected:
            QTreeWidget* tree_ptr = nullptr;
            QTreeWidgetItem* m_last_changed_item = nullptr;

            void setup_tree() {
                tree_ptr->setHeaderLabels({"Addr", "Hex", "Binary", "Dec", "Str"});
                tree_ptr->setRootIsDecorated(false);
                tree_ptr->setSelectionMode(QAbstractItemView::SingleSelection);
            }

            void append_row(std_word_t addr, std_word_t val) {
                auto* item = new QTreeWidgetItem(tree_ptr);

                item->setData(0, Qt::UserRole, addr);  // store raw addr for lookup

                set_row_values(item, addr, val);
            }

            void set_row_values(QTreeWidgetItem* item, std_word_t addr, std_word_t val) {
                item->setText(0, format_hex(addr));
                item->setText(1, format_hex(val));
                item->setText(2, format_binary(val));
                item->setText(3, QString::number(val));
                item->setText(4, printable_char(val));
            }

            bool is_mmio(std_word_t addr) {
                return addr >= (std_word_t)vm::mmio::KBSR && addr <= (std_word_t)vm::mmio::MCR;
            }
    };

} // namespace lc3kit::ide
