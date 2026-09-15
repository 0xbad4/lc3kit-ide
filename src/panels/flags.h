#pragma once

#include "base.h"
#include "widgets/wflags.h"


namespace lc3kit::ide {

    class FlagsRegister : public QWidget, public BaseController {
        Q_OBJECT

        public:
            explicit FlagsRegister(QWidget*wptr) : QWidget(wptr), parentw_ptr(wptr) {
                setup_widget();
            }

            ~FlagsRegister() {
                if (m_flags_w) delete m_flags_w;
            }

            QString name() {
                return "Program Status";
            }

            void load(vm_ptr_t rvm) {
                std_word_t psr = rvm->reg_read(vm::registers::PSR);

                update_ui(psr);
            }

            void on_register_changed(vm_ptr_t, vm::registers reg, std_word_t nv) {
                // if not Program Status Register (flags) that changed, ignore.
                if (reg != vm::registers::PSR) {
                    return;
                }

                update_ui(nv);
            }

        protected:
            QWidget* parentw_ptr = nullptr;
            Ui::Flags* m_flags_w = nullptr;


            void update_ui(std_word_t psr) {
                if (!m_flags_w) {
                    qCritical() << name() << ": flags widget is null — cannot update UI (internal state error)";
                    return;
                }

                qDebug() << name() << ": updating UI with new register state"
                         << "PSR =" << format_hex(psr);

                bool PL  = bit(psr, 15);
                bool PR2 = bit(psr, 10);
                bool PR1 = bit(psr, 9);
                bool PR0 = bit(psr, 8);
                bool N   = bit(psr, 2);
                bool Z   = bit(psr, 1);
                bool P   = bit(psr, 0);

                m_flags_w->flag_negative->setChecked(N);
                m_flags_w->flag_zero->setChecked(Z);
                m_flags_w->flag_positive->setChecked(P);
                
                m_flags_w->flags_z->setChecked(Z);
                m_flags_w->flags_n->setChecked(N);
                m_flags_w->flags_p->setChecked(P);
                
                m_flags_w->flags_pl->setChecked(PL);
                m_flags_w->flags_pr2->setChecked(PR2);
                m_flags_w->flags_pr1->setChecked(PR1);
                m_flags_w->flags_pr0->setChecked(PR0);

                qDebug() << name() << ": flags updated"
                         << "N=" << N << "Z=" << Z << "P=" << P
                         << "PL=" << PL;
            }

            void setup_widget() {
                qDebug() << name() << ": setting up panel widget";

                if (parentw_ptr->layout()) {
                    m_flags_w = new Ui::Flags();

                    m_flags_w->setupUi(this);
                    parentw_ptr->layout()->addWidget(this);
                    qDebug() << name() << ": widget added to parent layout";
                }
                else {
                    qCritical() << name() << ": parent widget has no layout — panel will not be visible (internal state error)";
                    return;
                }

                auto label_n = new QLabel(this);
                auto label_z = new QLabel(this);
                auto label_p = new QLabel(this);

                label_n->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
                label_z->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
                label_p->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);

                label_n->setText("Negative");
                label_z->setText("Zero");
                label_p->setText("Positive");

                m_flags_w->flag_negative->setLayout(new QHBoxLayout());
                m_flags_w->flag_zero->setLayout(new QHBoxLayout());
                m_flags_w->flag_positive->setLayout(new QHBoxLayout());

                m_flags_w->flag_negative->layout()->addWidget(label_n);
                m_flags_w->flag_zero->layout()->addWidget(label_z);
                m_flags_w->flag_positive->layout()->addWidget(label_p);

                update_ui(0);
                qInfo() << name() << ": panel initialized and ready";
            }

    };

} // namespace lc3kit::ide
