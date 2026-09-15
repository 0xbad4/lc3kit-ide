#pragma once

#include <QObject>
#include <QString>
#include <QIcon>
#include <QFile>
#include <QHash>
#include <QColor>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <algorithm>
#include <limits>
#include <optional>
#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QHash>

namespace lc3kit::ide {

    typedef enum {
        MEMORY_POPULATE_ALL,    // bool: true=full 64KB, false=program only
        EXT_ENABLED,            // bool
        THEME_NAME,             // string
        ASM_ON_SAVE,            // bool
        ASM_EVERY_RUN,          // bool
    } qsetting_key;

    // User settings only
    class USettings : public QObject {
        Q_OBJECT

        private:
            explicit USettings(QObject* parent = nullptr) : QObject(parent), m_settings("lc3kit-ide", "IDE") {
                // Initialize defaults only if the key doesn't exist.
                init_default(qsetting_key::MEMORY_POPULATE_ALL, false);
                init_default(qsetting_key::EXT_ENABLED,         true);
                init_default(qsetting_key::THEME_NAME,          QString("charcoal"));
                init_default(qsetting_key::ASM_ON_SAVE,         false);
                init_default(qsetting_key::ASM_EVERY_RUN,       true);
            }

            USettings(const USettings&) = delete;
            USettings& operator=(const USettings&) = delete;

            QSettings m_settings;

            static QString key_name(qsetting_key key) {
                switch (key) {
                    case qsetting_key::MEMORY_POPULATE_ALL: return "memory/populate_all";
                    case qsetting_key::EXT_ENABLED:         return "assembler/ext_enabled";
                    case qsetting_key::THEME_NAME:          return "application/theme";
                    case qsetting_key::ASM_ON_SAVE:         return "assembler/assemble_on_save";
                    case qsetting_key::ASM_EVERY_RUN:       return "assembler/assemble_every_run";
                }

                return {};
            }

            // per-key hard fallback — only reached if a value is missing AND the
            // caller didn't pass their own fallback to get()/get_*(). In practice
            // init_default() above means this rarely fires; it's a safety net for a
            // key added to the enum without a matching init_default() call, or a
            // settings file edited/corrupted outside the app.
            static QVariant hard_fallback(qsetting_key key) {
                switch (key) {
                    case qsetting_key::MEMORY_POPULATE_ALL: return false;
                    case qsetting_key::EXT_ENABLED:         return true;
                    case qsetting_key::THEME_NAME:          return QString("charcoal");
                    case qsetting_key::ASM_ON_SAVE:         return false;
                    case qsetting_key::ASM_EVERY_RUN:       return true;
                }

                return {};
            }

            void init_default(qsetting_key key, const QVariant& value) {
                const auto name = key_name(key);
                if (!m_settings.contains(name))
                    m_settings.setValue(name, value);
            }

        public:
            static USettings& instance() {
                static USettings s_instance;
                return s_instance;
            }

            // raw QVariant read. Fallback resolution order: stored value -> `fallback`
            // (if you passed one) -> the key's built-in hard_fallback().
            QVariant get(qsetting_key key, const QVariant& fallback = QVariant()) const {
                QVariant v = m_settings.value(key_name(key));
                if (v.isValid())      return v;
                if (fallback.isValid()) return fallback;
                return hard_fallback(key);
            }

            bool get_bool(qsetting_key key, const QVariant& fallback = QVariant()) const {
                return get(key, fallback).toBool();
            }

            QString get_string(qsetting_key key, const QVariant& fallback = QVariant()) const {
                return get(key, fallback).toString();
            }

            double get_number(qsetting_key key, const QVariant& fallback = QVariant()) const {
                return get(key, fallback).toDouble();
            }

            void set(qsetting_key key, const QVariant& value) {
                const auto name = key_name(key);

                if (m_settings.value(name) == value)
                    return;

                m_settings.setValue(name, value);
                emit changed(key, value);
            }

        signals:
            void changed(qsetting_key key, const QVariant& value);
    };

    inline USettings& settings = USettings::instance();

    // Opens a Qt resource, parses it as JSON, and logs a consistent
    // warning on either a missing file or a malformed document.
    // Every JSON resource this class reads (editor palette, qss
    // palette, themes list) goes through this one place instead of
    // repeating the same open/parse/error-log boilerplate.
    inline std::optional<QJsonDocument> load_json_document(const QString& resource_path, const QString& what) {
        QFile file(resource_path);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "json:" << what << "resource not found"
                        << "resource =" << resource_path
                        << "error =" << file.errorString();
            return std::nullopt;
        }

        QJsonParseError error;
        const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);

        if (error.error != QJsonParseError::NoError) {
            qWarning() << "json:" << what << "JSON parsing failed"
                        << "resource =" << resource_path
                        << "error =" << error.errorString();
            return std::nullopt;
        }

        return document;
    }

} // namespace lc3kit::ide
