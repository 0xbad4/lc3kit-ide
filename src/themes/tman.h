#pragma once
#include <limits>
#include <algorithm>

#include "utils/common.h"

#include "utils/settings.h"
#include "utils/manifest.h"
#include "themes/palettes.h"
#include "themes/proxy.h"

namespace lc3kit::ide
{
    class ThemeManager : public QObject {
        Q_OBJECT

        private:
            explicit ThemeManager(QObject* parent = nullptr) : QObject(parent) {
                load_theme();
            }

            ThemeManager(const ThemeManager&)            = delete;
            ThemeManager& operator=(const ThemeManager&) = delete;
            ThemeManager(ThemeManager&&)                 = delete;
            ThemeManager& operator=(ThemeManager&&)      = delete;

            TextEditorPalette       m_te_palette;
            QSSPalette              m_qss_palette;
            QHash<QString, QString> m_qss_vars;
            QString                 m_theme_name;

            void load_theme(QString name="") {
                if (name.isEmpty()) {
                    name = settings.get_string(THEME_NAME);
                    qDebug() << "ThemeManager: loading theme from settings:" << name;
                }

                if (theme_exists(name)) {
                    m_theme_name = name;
                    load_editor_palette();
                    load_qss_palette();
                    qInfo() << "ThemeManager: theme loaded successfully" << "name =" << name;
                    return;
                }

                qWarning() << "ThemeManager: requested theme not found"
                           << "requested =" << name
                           << "— attempting automatic fallback";

                QList<QString> ths = themes();
                qDebug() << "ThemeManager: available themes =" << ths.size() << "themes =" << ths;

                for (const auto& thn : ths) {
                    if (theme_exists(thn)) {
                        qInfo() << "ThemeManager: loading fallback theme" << "fallback =" << thn;
                        load_theme(thn);  // load the first available theme
                        return;
                    }
                }

                qCritical() << "ThemeManager: no usable themes found in resource — application will have no visual style";
            }

            void load_editor_palette() {
                const QString resource_path = QString(":/%1/style/editor").arg(m_theme_name);

                qDebug() << "ThemeManager: loading editor palette"
                         << "theme =" << m_theme_name
                         << "resource =" << resource_path;

                const auto document = load_json_document(resource_path, "editor theme");

                if (!document || !document->isObject()) {
                    DLERROR(QString("Editor theme %1 not found or corrupted").arg(m_theme_name));
                    return;
                }

                qDebug() << "ThemeManager: editor theme loaded and parsed successfully" << "theme =" << m_theme_name;

                const QJsonObject json = document->object();

                auto load_color = [&](const char* key, QColor& target) {
                    const auto value = json.value(key);

                    if (value.isString()) {
                        const QColor color(value.toString());

                        if (color.isValid()) {
                            target = color;
                        }
                    }
                };

                auto load_string = [&](const char* key, QString& target) {
                    const auto value = json.value(key);

                    if (value.isString()) {
                        target = value.toString();
                    }
                };

                auto load_uint = [&](const char* key, uint& target) {
                    const auto value = json.value(key);

                    if (value.isDouble()) {
                        const double number = value.toDouble();

                        if (number >= 0 &&
                            number <= std::numeric_limits<uint>::max()) {
                            target = static_cast<uint>(number);
                        }
                    }
                };

                auto load_bool = [&](const char* key, bool& target) {
                    const auto value = json.value(key);

                    if (value.isBool()) {
                        target = value.toBool();
                    }
                };

                // Editor
                load_color("editor-background", m_te_palette.editor_background);
                load_color("editor-foreground", m_te_palette.editor_foreground);
                load_string("editor-font", m_te_palette.editor_font);
                load_uint("editor-font-size", m_te_palette.editor_font_size);

                // Margins
                load_color("margin-background", m_te_palette.margin_background);
                load_color("margin-foreground", m_te_palette.margin_foreground);

                // Caret / selection
                load_color("caret-foreground", m_te_palette.caret_foreground);
                load_color("caret-line-background", m_te_palette.caret_line_background);
                load_color("selection-background", m_te_palette.selection_background);

                // Markers
                load_color("marker-pc-foreground", m_te_palette.marker_pc_foreground);
                load_color("marker-pc-background", m_te_palette.marker_pc_background);
                load_color("marker-breakpoint-foreground", m_te_palette.marker_breakpoint_foreground);
                load_color("marker-breakpoint-background", m_te_palette.marker_breakpoint_background);
                load_color("marker-error-background", m_te_palette.marker_error_background);

                // Indicators
                load_color("indicator-search-foreground", m_te_palette.indicator_search_foreground);
                load_color("indicator-pc-foreground", m_te_palette.indicator_pc_foreground);

                // Syntax
                load_color("syntax-default-foreground", m_te_palette.syntax_default_foreground);
                load_color("syntax-comment-foreground", m_te_palette.syntax_comment_foreground);
                load_color("syntax-mnemonic-foreground", m_te_palette.syntax_mnemonic_foreground);
                load_color("syntax-directive-foreground", m_te_palette.syntax_directive_foreground);
                load_color("syntax-register-foreground", m_te_palette.syntax_register_foreground);
                load_color("syntax-label-foreground", m_te_palette.syntax_label_foreground);
                load_color("syntax-number-foreground", m_te_palette.syntax_number_foreground);
                load_color("syntax-string-foreground", m_te_palette.syntax_string_foreground);
                load_color("syntax-trap-foreground", m_te_palette.syntax_trap_foreground);

                // Syntax attributes
                load_bool("syntax-mnemonic-bold", m_te_palette.syntax_mnemonic_bold);
                load_bool("syntax-comment-italic", m_te_palette.syntax_comment_italic);
                load_bool("syntax-trap-bold", m_te_palette.syntax_trap_bold);
            }

            void load_qss_palette() {
                const QString resource_path = QString(":/%1/style/palette").arg(m_theme_name);

                qDebug() << "ThemeManager: loading qss palette"
                         << "theme =" << m_theme_name
                         << "resource =" << resource_path;

                const auto document = load_json_document(resource_path, "qss palette");

                if (!document || !document->isObject()) {
                    DLERROR(QString("QSS palette for theme %1 not found or corrupted").arg(m_theme_name));
                    return;
                }

                const QJsonObject json = document->object();

                auto load_color = [&](const char *key, QColor& target) {
                    const QJsonValue value = json.value(key);

                    if (!value.isString())
                        return;

                    const QColor color(value.toString());

                    if (color.isValid())
                        target = color;
                };

                load_color("bg-0",         m_qss_palette.bg_0);
                load_color("bg-1",         m_qss_palette.bg_1);
                load_color("bg-2",         m_qss_palette.bg_2);
                load_color("bg-3",         m_qss_palette.bg_3);
                load_color("bg-inset",     m_qss_palette.bg_inset);

                load_color("border-soft",  m_qss_palette.border_soft);

                load_color("text-0",       m_qss_palette.text_0);
                load_color("text-1",       m_qss_palette.text_1);
                load_color("text-2",       m_qss_palette.text_2);

                load_color("accent-soft",  m_qss_palette.accent_soft);
                load_color("accent-hi",    m_qss_palette.accent_hi);
                load_color("accent-text",  m_qss_palette.accent_text);

                load_color("border",       m_qss_palette.border);
                load_color("accent",       m_qss_palette.accent);

                load_color("ok",           m_qss_palette.ok);
                load_color("warn",         m_qss_palette.warn);
                load_color("danger",       m_qss_palette.danger);
                load_color("violet",       m_qss_palette.violet);

                // Keep the raw string values around too (not just QColor),
                // so the QSS stylesheet's "$key" placeholders can be
                // resolved by plain text substitution — see
                // resolve_qss_variables(). This also means any key added
                // to the palette JSON is picked up automatically without
                // touching this function.
                m_qss_vars.clear();

                for (auto it = json.begin(); it != json.end(); ++it) {
                    if (it.value().isString()) {
                        m_qss_vars.insert(it.key(), it.value().toString());
                    }
                }
            }

            bool theme_exists(const QString& name) const {
                return QFile::exists(QString(":/%1/style/qss").arg(name));
            }

            void resolve_qss_variables(QString& sheet) const {
                QList<QString> keys = m_qss_vars.keys();

                std::sort(keys.begin(), keys.end(), [](const QString& a, const QString& b) {
                    return a.length() > b.length();
                });

                for (const auto& key : keys) {
                    sheet.replace(QLatin1Char('$') + key, m_qss_vars.value(key));
                }
            }

        public:
            static ThemeManager& instance() {
                static ThemeManager s_instance;
                return s_instance;
            }
            
            bool theme(const QString& name) {
                if (!theme_exists(name)) {
                    DLERROR(QString("Theme %1 not found").arg(name));
                    return false;
                }

                if (name == m_theme_name) {
                    return true; // already active, nothing to reload
                }

                settings.set(THEME_NAME, name);
                load_theme(name);
                DLLOG(QString("Theme updated to %1").arg(name));
                return true;
            }

            QList<QString> themes() {
                return appmanifest.themes();
            }

            QIcon icon(const QString& name) {
                const QString resource_path = QString(":/%1/icons/%2").arg(m_theme_name).arg(name);

                if (!QFile::exists(resource_path)) {
                    qWarning() << "ThemeManager: icon not found"
                               << "theme =" << m_theme_name
                               << "name =" << name
                               << "resource =" << resource_path;
                }

                return QIcon(resource_path);
            }

            QString qss() {
                const QString resource_path = QString(":/%1/style/qss").arg(m_theme_name);
                QFile file(resource_path);

                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qWarning() << "ThemeManager: QSS stylesheet not found for theme"
                               << "theme =" << m_theme_name
                               << "resource =" << resource_path;
                    return {};
                }

                QString sheet = QString::fromUtf8(file.readAll());
                resolve_qss_variables(sheet);
                return sheet;
            }

            const QSSPalette& qssp() const {
                return m_qss_palette;
            }

            const TextEditorPalette& edp() const {
                return m_te_palette;
            }
        };

    #define theman  ThemeManager::instance()
    #define edpalette  ThemeManager::instance().edp()
    #define qsspalette ThemeManager::instance().qssp()
    #define THEMES() ThemeManager::instance().themes()
    #define ICON(NAME) ThemeManager::instance().icon(NAME)
    #define QSS()    ThemeManager::instance().qss()

} // namespace lc3kit::ide