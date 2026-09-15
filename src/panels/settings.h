#pragma once

#include "base.h"
#include "dialogs/file.h"
#include "widgets/wsettings.h"

namespace lc3kit::ide {
    class Settings : public QWidget, public BaseController {
        Q_OBJECT

        public:
            explicit Settings(QWidget*wptr) : QWidget(wptr), parentw_ptr(wptr) {
                setup_widget();
            }

            ~Settings() {
                if (m_settings_w) {
                    delete m_settings_w;
                }
            }

            QString name() {
                return "Settings";
            }

        signals:
            void settings_changed(qsetting_key, QVariant);

        protected:
            QWidget*      parentw_ptr  = nullptr;
            Ui::Settings* m_settings_w = nullptr;

            void setup_widget() {
                qDebug() << name() << ": setting up settings panel";

                if (parentw_ptr->layout()) {
                    m_settings_w = new Ui::Settings;
                    
                    m_settings_w->setupUi(this);
                    parentw_ptr->layout()->addWidget(this);
                    qDebug() << name() << ": panel added to parent layout";
                }
                else {
                    qCritical() << name() << ": parent widget has no layout — panel will not be visible (internal state error)";
                    DLERROR("parent widget has no layout", name());
                    return;
                }

                setContentsMargins(2, 2, 2, 2);
                
                load_settings();

                // signals
                connect(m_settings_w->view_all_mem, &QCheckBox::stateChanged, this, &Settings::on_mem_view_all_changed);
                connect(m_settings_w->ext_en, &QCheckBox::stateChanged, this, &Settings::on_ext_en_changed);
                connect(m_settings_w->asm_on_run, &QCheckBox::stateChanged, this, &Settings::on_asm_on_run_changed);
                connect(m_settings_w->asm_on_save, &QCheckBox::stateChanged, this, &Settings::on_asm_on_save_changed);
                connect(m_settings_w->theme_opts, &QComboBox::currentTextChanged, this, &Settings::on_theme_opt_changed);

                qInfo() << name() << ": panel initialized and ready";
            }

            void load_settings() {
                qDebug() << name() << ": loading application settings";
                m_settings_w->theme_opts->clear();
                for (auto& t : theman.themes()) {
                    t[0] = t[0].toUpper();
                    m_settings_w->theme_opts->addItem(t);
                }

                m_settings_w->view_all_mem->setChecked(settings.get_bool(MEMORY_POPULATE_ALL));
                m_settings_w->ext_en->setChecked(      settings.get_bool(EXT_ENABLED));
                m_settings_w->asm_on_run->setChecked(  settings.get_bool(ASM_EVERY_RUN));
                m_settings_w->asm_on_save->setChecked( settings.get_bool(ASM_ON_SAVE));

                auto tn = settings.get_string(THEME_NAME);
                tn[0] = tn[0].toUpper();
                m_settings_w->theme_opts->setCurrentText(tn);
                
                qDebug() << name() << ": settings loaded from persistent storage";
            }

            void on_mem_view_all_changed(bool sts) {
                qDebug() << name() << ": memory view mode changed" << "populate_all =" << sts;
                settings.set(MEMORY_POPULATE_ALL, sts);
                emit settings_changed(MEMORY_POPULATE_ALL, sts);
            }

            void on_ext_en_changed(bool sts) {
                qDebug() << name() << ": EXT extension setting changed" << "enabled =" << sts;
                settings.set(EXT_ENABLED, sts);
                emit settings_changed(EXT_ENABLED, sts);
            }

            void on_asm_on_save_changed(bool sts) {
                qDebug() << name() << ": assemble on save setting changed" << "enabled =" << sts;
                settings.set(ASM_ON_SAVE, sts);
                emit settings_changed(ASM_ON_SAVE, sts);
            }

            void on_asm_on_run_changed(bool sts) {
                qDebug() << name() << ": assemble on run setting changed" << "enabled =" << sts;
                settings.set(ASM_EVERY_RUN, sts);
                emit settings_changed(ASM_EVERY_RUN, sts);
            }

            void on_theme_opt_changed(const QString &t) {
                qDebug() << name() << ": theme changed" << "name =" << t;
                settings.set(THEME_NAME, t.toLower());
                emit settings_changed(THEME_NAME, t.toLower());
            }
    };

} // namespace lc3kit::ide
