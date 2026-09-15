#pragma once

#include "widgets/wdefault_tab.h"
#include "themes/tman.h"
#include <QPixmap>
 
namespace lc3kit::ide {
    class DefaultTab : public QWidget {
        Q_OBJECT

        public:
            explicit DefaultTab(QWidget* parent = nullptr) : QWidget(parent), m_default_tab_ui(new Ui::DefaultTab) {
                setup_ui();
            }

            void setup_ui() {
                m_default_tab_ui->setupUi(this);
                setup_icons();
            }

            void setup_icons() {
                m_default_tab_ui->file_icon->setPixmap(ICON("default-tab-file").pixmap(300, 300));
            }

            ~DefaultTab() {
                if (m_default_tab_ui) {
                    delete m_default_tab_ui;
                }
            }

        protected:
            Ui::DefaultTab* m_default_tab_ui = nullptr;
    };
}
