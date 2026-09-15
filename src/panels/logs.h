#pragma once

#include "base.h"

namespace lc3kit::ide
{
    class Logs : public QObject, public BaseController {
        Q_OBJECT

        public:
            explicit Logs(QTreeWidget* tptr) : QObject(tptr), tree_ptr(tptr) {
                setup_tree();
            }

            QString name() {
                return "Logs";
            }

            void log(const qlog_event& event) {
                auto* item = new QTreeWidgetItem(tree_ptr);

                item->setText(0, event.sender);
                item->setText(1, event.message); 

                tree_ptr->addTopLevelItem(item);

                // level badge
                switch (event.level) {
                    case qlog_level::LOG:
                        item->setIcon(0, ICON("log-log"));
                        break;
                    case qlog_level::WARN:
                        item->setIcon(0, ICON("log-warn"));
                        break;
                    case qlog_level::ERROR:
                        item->setIcon(0, ICON("log-error"));
                        break;
                }
                // auto-scroll to latest
                tree_ptr->scrollToItem(item);
            }

        protected:
            QTreeWidget* tree_ptr = nullptr;
            
            void setup_tree() {
                tree_ptr->setHeaderLabels({"Sender", "Message"});
                tree_ptr->setRootIsDecorated(false);
                // message column stretches
                tree_ptr->header()->setSectionResizeMode(2, QHeaderView::Stretch);
            }

    };

} // namespace lc3kit::ide
