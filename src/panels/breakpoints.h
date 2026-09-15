#pragma once

#include "base.h"

namespace lc3kit::ide
{

    class Breakpoints : public QObject, public BaseController {
        Q_OBJECT

        public:
            explicit Breakpoints(QTreeWidget*tptr) : QObject(tptr), tree_ptr(tptr) { 
                setup_tree();
            }

            QString name() {
                return "Breakpoints";
            }

            void load(const QSet<std_word_t>& addresses, const lasm::sym_table_t& symptr) {
                qDebug() << name() << ": loading breakpoints"
                         << "count =" << addresses.size();

                tree_ptr->setUpdatesEnabled(false);
                tree_ptr->clear();

                for (const auto& addr : addresses) {
                    qDebug() << name() << ": adding breakpoint to display"
                             << "address =" << format_hex(addr);
                    append_row(addr, get_label(addr, symptr));
                }

                tree_ptr->setUpdatesEnabled(true);
                qInfo() << name() << ": breakpoints display updated"
                        << "total_displayed =" << tree_ptr->topLevelItemCount();
            }

            void on_breakpoint(vm_ptr_t, std_word_t addr) {
                qInfo() << name() << ": breakpoint hit"
                        << "address =" << format_hex(addr);
                
                // locate item
                QTreeWidgetItem* item = nullptr;

                for (int i = 0; i < tree_ptr->topLevelItemCount(); i++) {
                    item = tree_ptr->topLevelItem(i);

                    if (item_addr(item) != addr) {
                        item = nullptr;
                    }
                }

                if (!item) {
                    qWarning() << name() << ": breakpoint hit at address"
                               << format_hex(addr)
                               << "but breakpoint not found in display";
                    DLWARN(QString("Breakpoint @ x%1 not loaded").arg(addr, 4, 16, QChar('0')).toUpper(), name());
                    return;
                }

                qDebug() << name() << ": highlighting breakpoint in display" << "address =" << format_hex(addr);

                mark_last_changed(m_last_changed_item, item);
            }

        protected:
            QTreeWidget* tree_ptr = nullptr;
            QTreeWidgetItem* m_last_changed_item = nullptr;

            void setup_tree() {
                tree_ptr->setColumnCount(2);
                tree_ptr->setHeaderLabels({"Addr", "Label"});
                tree_ptr->setRootIsDecorated(false);
                tree_ptr->setSelectionMode(QAbstractItemView::SingleSelection);
            }

            void append_row(std_word_t addr, const QString& label) {
                auto* item = new QTreeWidgetItem(tree_ptr);

                item->setData(0, Qt::UserRole, addr);  // store raw addr for lookup
                set_row_values(item, addr, label);
            }

            void set_row_values(QTreeWidgetItem* item, std_word_t addr, const QString& label) {
                item->setText(0, format_hex(addr));
                item->setText(1, label);
            }

            QString get_label(std_word_t addr, const lasm::sym_table_t& symptr) {
                if (symptr.empty()) {
                    return "";
                }

                for (const auto& item : symptr) {
                    if (item.second == addr) {
                        return QString::fromStdString(item.first);
                    }
                }

                return "";
            }
    };

} // namespace lc3kit::ide
