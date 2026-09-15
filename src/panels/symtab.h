#pragma once

#include "base.h"

namespace lc3kit::ide
{
    class SymTable : public QObject, public BaseController {
        Q_OBJECT

        public:
            explicit SymTable(QTreeWidget* tptr) : QObject(tptr), tree_ptr(tptr) {
                setup_tree();
            }

            QString name() {
                return "SymTab";
            }

            void load(const lasm::sym_table_t& symbols, const lasm::lines_addrs_t& lines) {
                tree_ptr->clear();
                tree_ptr->setUpdatesEnabled(false);

                for (auto it = symbols.cbegin(); it != symbols.cend(); ++it) {
                    auto* item = new QTreeWidgetItem(tree_ptr);
                    item->setText(0, QString::fromStdString(it->first));
                    item->setText(1, format_hex(it->second));
                    item->setText(2, QString("%1").arg(addr_line(it->second, lines)+1));
                }

                tree_ptr->sortByColumn(1, Qt::AscendingOrder);  // sort by address
                tree_ptr->setUpdatesEnabled(true);
            }

        protected:
            QTreeWidget* tree_ptr = nullptr;

            uint addr_line(std_word_t o, const lasm::lines_addrs_t& lines) {
                for (const auto& s : lines) {
                    if (s.second == o) {
                        return s.first;
                    }
                }
                return uint(0);
            };

            void setup_tree() {
                tree_ptr->setColumnCount(2);
                tree_ptr->setHeaderLabels({"Symbol", "Addr", "Line"});
                tree_ptr->setRootIsDecorated(false);
            }
    };

} // namespace lc3kit::ide
