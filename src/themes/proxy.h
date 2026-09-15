#pragma once

#include <QProxyStyle>
#include <QStyleOption>
#include <QPainter>
#include <QStyledItemDelegate>

namespace lc3kit::ide {
    class ProxyStyle : public QProxyStyle {
        public:
            explicit ProxyStyle(QStyle *base = nullptr,
                                        int dockSeparatorPx = 2,
                                        int toolBarSeparatorPx = 1)
                : QProxyStyle(base),
                m_dockSeparator(dockSeparatorPx),
                m_toolBarSeparator(toolBarSeparatorPx) {}

            int pixelMetric(PixelMetric metric,
                            const QStyleOption *option = nullptr,
                            const QWidget *widget = nullptr) const override {
                switch (metric) {
                    case QStyle::PM_DockWidgetSeparatorExtent: // QMainWindow dock gaps
                    case QStyle::PM_SplitterWidth:             // QSplitter handles
                        return m_dockSeparator;
                    case QStyle::PM_ToolBarSeparatorExtent:    // QToolBar::separator
                        return m_toolBarSeparator;
                    default:
                        return QProxyStyle::pixelMetric(metric, option, widget);
                }
            }

            int styleHint(StyleHint hint,
                        const QStyleOption *option = nullptr,
                        const QWidget *widget = nullptr,
                        QStyleHintReturn *returnData = nullptr) const override {
                switch (hint) {
                    case QStyle::SH_TabBar_Alignment:
                        return Qt::AlignLeft;
                    default:
                        return QProxyStyle::styleHint(hint, option, widget, returnData);
                }
            }

        private:
            int m_dockSeparator;
            int m_toolBarSeparator;
    };
} // namespace lc3kit::ide
