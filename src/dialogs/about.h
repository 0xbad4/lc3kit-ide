#pragma once

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>

#include "widgets/wabout.h"
#include "utils/manifest.h"
#include "themes/proxy.h"

namespace lc3kit::ide
{
    class AboutDialog : public QDialog {
        Q_OBJECT

        public:
            explicit AboutDialog(QWidget* parent = nullptr) : QDialog(parent), m_ui(new Ui::About) {
                setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
                setup_ui();
            }

            ~AboutDialog() override {
                delete m_ui;
            }

        protected:
            Ui::About* m_ui = nullptr;

            void setup_ui() {
                m_ui->setupUi(this);
                setup_app_info();
                setup_links();
                setup_dev_info();
                setup_footer();
            }

        private:
            void setup_app_info() {
                m_ui->app_icon->setPixmap(QIcon(":/img/lc3kit-ide").pixmap(64, 64));
                m_ui->app_name->setText(appmanifest.pretty_name());
                m_ui->app_ver->setText(QString("Version %1").arg(appmanifest.version()));
            }

            void setup_links() {
                m_ui->docs_icon->setPixmap(ICON("documentation").pixmap(30, 30));
                m_ui->src_code_icon->setPixmap(ICON("github").pixmap(30, 30));
                m_ui->developer_icon->setPixmap(ICON("person").pixmap(30, 30));

                connect(m_ui->docs_open, &QPushButton::clicked, this, [] {
                    QDesktopServices::openUrl(QUrl(appmanifest.documentation()));
                });

                connect(m_ui->src_code_open, &QPushButton::clicked, this, [] {
                    QDesktopServices::openUrl(QUrl(appmanifest.source()));
                });

                connect(m_ui->developer_profile_open, &QPushButton::clicked, this, [] {
                    QDesktopServices::openUrl(QUrl(appmanifest.developer()));
                });
            }

            void setup_dev_info() {
                m_ui->qt_ver->setText(QT_VERSION_STR);
                m_ui->cpp_ver->setText(cpp_standard_label());
                m_ui->lib_ver->setText(__LC3_KIT_LIB_VERSION);
            }

            void setup_footer() {
                m_ui->heart_icon->setPixmap(theman.icon("heart").pixmap(16, 16));

                connect(m_ui->developer_profile_open2, &QPushButton::clicked, this, [] {
                    QDesktopServices::openUrl(QUrl(appmanifest.developer()));
                });

                connect(m_ui->close_win, &QPushButton::clicked, this, &QDialog::accept);
            }

            static QString cpp_standard_label() {
                #if __cplusplus >= 202302L
                                return "C++23";
                #elif __cplusplus >= 202002L
                                return "C++20";
                #elif __cplusplus >= 201703L
                                return "C++17";
                #elif __cplusplus >= 201402L
                                return "C++14";
                #elif __cplusplus >= 201103L
                                return "C++11";
                #else
                                return "C++98";
                #endif
            }
        };

} // namespace lc3kit::ide