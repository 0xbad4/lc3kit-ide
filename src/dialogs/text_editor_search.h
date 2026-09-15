#pragma once

#include <QPropertyAnimation>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QTimer>
#include "widgets/wtext_editor_search.h"

namespace lc3kit::ide
{
    class TextEditorSearch : public QWidget {
        Q_OBJECT

        public:
            explicit TextEditorSearch(QWidget* wptr=nullptr) : QWidget(wptr), m_search_w(new Ui::TESearch) {
                setup_widget();
                close();
            }

            ~TextEditorSearch() {
                if (m_search_w) {
                    delete m_search_w;
                }
            }

            void init_term(QString t) {
                m_search_w->search_term->setText(t);
                m_search_w->search_term->selectAll();
            }

            QString term() {
                return m_search_w->search_term->text();
            }

            void current(int ind) {
                m_search_w->search_current_label->setText(QString("%1").arg(ind+1));
            }

            void total(int tot) {
                m_search_w->search_count->setText(QString("%1").arg(tot));
                current(tot > 0 ? 0 : -1);
            }

            void show() {
                if (!m_search_w->search_term->text().isEmpty()) {
                    m_search_w->search_term->selectAll();
                    emit search_text_changed(m_search_w->search_term->text());
                }
                QWidget::show();
            }

            // animated show
            void ashow() {
                m_animation->stop();

                const QPoint visiblePos(parentWidget()->width() - (width() + 2), 35);
                const QPoint hiddenPos(parentWidget()->width() + 50, 35);

                m_animation->setDuration(250);
                m_animation->setStartValue(hiddenPos);
                m_animation->setEndValue(visiblePos);
                
                m_search_w->search_term->setFocus();
                move(hiddenPos);
                show();
                raise();
                m_animation->start();
                qDebug() << "Search popup animated show started";
            }

            // animated hide
            void aclose() {
                m_animation->stop();

                const QPoint hiddenPos(parentWidget()->width() + 50, 35);

                m_animation->setDuration(250);
                m_animation->setStartValue(pos());
                m_animation->setEndValue(hiddenPos);

                connect(m_animation, &QPropertyAnimation::finished,
                        this, &TextEditorSearch::on_out_of_sight, Qt::SingleShotConnection);

                m_animation->start();
            }

            void setup_icons() {
                m_search_w->search_close->setIcon(ICON("dock-close"));
                m_search_w->search_next->setIcon(ICON("search-next"));
                m_search_w->search_previous->setIcon(ICON("search-previous"));
                m_search_w->search_replace_current->setIcon(ICON("search-replace"));
                m_search_w->search_replace_all->setIcon(ICON("search-replace-all"));
            }

        signals:
            void search_text_changed(const QString& text);
            void next_requested();
            void previous_requested();
            void replace_current_requested(const QString& repl);
            void replace_all_requested(const QString& repl);
            void closed();

        protected:
            Ui::TESearch* m_search_w = nullptr;
            QPropertyAnimation* m_animation = nullptr;
            QPropertyAnimation* m_fade = nullptr;
            QParallelAnimationGroup* m_anim_group = nullptr;

            void closeEvent(QCloseEvent* event) override {
                qDebug() << "Search popup closed";
                emit closed();
                QWidget::closeEvent(event);
            }

            void on_out_of_sight() {
                emit closed();
                hide();
            }

            void paintEvent(QPaintEvent*event) {
                QPainter painter(this);

                painter.setPen(QPen(qsspalette.border, 1));
                painter.setBrush(qsspalette.bg_2);

                painter.drawRect(QRect(QPoint(0, 0), size() - QSize(1, 1)));
            }

            void setup_widget() {
                m_search_w->setupUi(this);
                
                setup_icons();

                connect(m_search_w->search_term, &QLineEdit::textChanged, this, &TextEditorSearch::search_text_changed);
                connect(m_search_w->search_close, &QPushButton::clicked, this, &TextEditorSearch::aclose);
                connect(m_search_w->search_next, &QPushButton::clicked, this, &TextEditorSearch::next_requested);
                connect(m_search_w->search_previous, &QPushButton::clicked, this, &TextEditorSearch::previous_requested);

                connect(m_search_w->search_replace_current, &QPushButton::clicked, [this](){
                    emit replace_current_requested(m_search_w->search_replacement->text());
                });
                connect(m_search_w->search_replace_all, &QPushButton::clicked, [this](){
                    emit replace_all_requested(m_search_w->search_replacement->text());
                });

                // open/close animation
                m_animation = new QPropertyAnimation(this, "pos", this);
                m_animation->setDuration(250);
                m_animation->setEasingCurve(QEasingCurve::OutCubic);

                connect(m_animation, &QPropertyAnimation::finished, this, [this] {
                    if (pos().x() + width() <= 0)
                        hide();
                });

                // smoother
                auto* opacity = new QGraphicsOpacityEffect(this);
                opacity->setOpacity(1.0);
                setGraphicsEffect(opacity);

                m_fade = new QPropertyAnimation(opacity, "opacity", this);
                m_fade->setDuration(250);

                move(QPoint(-width(), pos().y()));
            }

            void fade_in() {
                show();

                m_fade->stop();
                m_fade->setStartValue(0.0);
                m_fade->setEndValue(1.0);
                m_fade->start();
            }

            void fade_out() {
                m_fade->stop();
                m_fade->setStartValue(1.0);
                m_fade->setEndValue(0.0);

                connect(m_fade, &QPropertyAnimation::finished, this, &QWidget::hide, Qt::SingleShotConnection);

                m_fade->start();
            }
    };
} // namespace lc3kit::ied
