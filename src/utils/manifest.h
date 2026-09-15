#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonValue>

#include "utils/common.h"
#include "utils/logger.h"

namespace lc3kit::ide
{
    class AppManifest : public QObject {
        Q_OBJECT

        private:
            explicit AppManifest(QObject* parent = nullptr) : QObject(parent) {
                load_manifest();
            }

            AppManifest(const AppManifest&)            = delete;
            AppManifest& operator=(const AppManifest&) = delete;
            AppManifest(AppManifest&&)                 = delete;
            AppManifest& operator=(AppManifest&&)      = delete;

            QString     m_name;
            QString     m_pretty_name;
            QString     m_version;
            QString     m_domain;
            QString     m_organization;
            QString     m_source;
            QString     m_documentation;
            QString     m_developer;
            QStringList m_themes;
            QStringList m_asm_examples;

            void load_manifest() {
                const auto document = load_json_document(":/app/manifest", "app manifest");

                if (!document || !document->isObject()) {
                    qCritical() << "AppManifest: failed to load app manifest from ':/app/manifest'";
                    return;
                }

                const QJsonObject manifest = document->object();

                m_name          = manifest.value("name").toString();
                m_pretty_name   = manifest.value("pretty-name").toString();
                m_version       = manifest.value("version").toString();
                m_domain        = manifest.value("domain").toString();
                m_organization  = manifest.value("organization").toString();
                m_organization  = manifest.value("organization").toString();
                m_source        = manifest.value("source").toString();
                m_documentation = manifest.value("documentation").toString();
                m_developer     = manifest.value("developer").toString();

                m_themes.clear();
                m_asm_examples.clear();

                auto load_string_array = [&](const char* key) -> QStringList {
                    const QJsonValue value = manifest.value(key);
                    QStringList result;

                    if (!value.isArray()) {
                        qWarning() << "AppManifest: manifest has no" << QString("'%1'").arg(key) << "array";
                        return result;
                    }

                    for (const QJsonValue& item : value.toArray()) {
                        if (item.isString()) {
                            result.append(item.toString());
                        }
                    }

                    return result;
                };

                m_themes = load_string_array("themes");
                m_asm_examples = load_string_array("asm-examples");

                qInfo() << "AppManifest: manifest loaded successfully"
                        << "name =" << m_name
                        << "version =" << m_version;
            }

        public:
            static AppManifest& instance() {
                static AppManifest s_instance;
                return s_instance;
            }

            const QString&     name()          const { return m_name; }
            const QString&     pretty_name()   const { return m_pretty_name; }
            const QString&     version()       const { return m_version; }
            const QString&     domain()        const { return m_domain; }
            const QString&     organization()  const { return m_organization; }
            const QString&     source()        const { return m_source; }
            const QString&     documentation() const { return m_documentation; }
            const QString&     developer()     const { return m_developer; }
            const QStringList& themes()        const { return m_themes; }
            const QStringList& asm_examples()  const { return m_asm_examples; }
        };

    #define appmanifest AppManifest::instance()

} // namespace lc3kit::ide
