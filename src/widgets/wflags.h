/********************************************************************************
** Form generated from reading UI file 'flagsqRbvAg.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FLAGSQRBVAG_H
#define FLAGSQRBVAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Flags
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *nzp_frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QCheckBox *flag_negative;
    QCheckBox *flag_zero;
    QCheckBox *flag_positive;
    QSpacerItem *horizontalSpacer_2;
    QFrame *other_flags_frame;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QCheckBox *flags_pl;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_4;
    QCheckBox *flags_pr2;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_10;
    QCheckBox *flags_pr1;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_12;
    QCheckBox *flags_pr0;
    QFrame *frame_12;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_6;
    QCheckBox *flags_n;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_8;
    QCheckBox *flags_z;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_14;
    QCheckBox *flags_p;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Flags)
    {
        if (Flags->objectName().isEmpty())
            Flags->setObjectName("Flags");
        Flags->resize(341, 169);
        Flags->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(Flags);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nzp_frame = new QFrame(Flags);
        nzp_frame->setObjectName("nzp_frame");
        nzp_frame->setFrameShape(QFrame::Shape::NoFrame);
        nzp_frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(nzp_frame);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        flag_negative = new QCheckBox(nzp_frame);
        flag_negative->setObjectName("flag_negative");
        flag_negative->setChecked(true);

        horizontalLayout_4->addWidget(flag_negative);

        flag_zero = new QCheckBox(nzp_frame);
        flag_zero->setObjectName("flag_zero");

        horizontalLayout_4->addWidget(flag_zero);

        flag_positive = new QCheckBox(nzp_frame);
        flag_positive->setObjectName("flag_positive");
        flag_positive->setChecked(false);

        horizontalLayout_4->addWidget(flag_positive);

        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(nzp_frame);

        other_flags_frame = new QFrame(Flags);
        other_flags_frame->setObjectName("other_flags_frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(other_flags_frame->sizePolicy().hasHeightForWidth());
        other_flags_frame->setSizePolicy(sizePolicy);
        other_flags_frame->setFrameShape(QFrame::Shape::NoFrame);
        other_flags_frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(other_flags_frame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        frame = new QFrame(other_flags_frame);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setFrameShape(QFrame::Shape::NoFrame);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        flags_pl = new QCheckBox(frame);
        flags_pl->setObjectName("flags_pl");
        flags_pl->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_pl->sizePolicy().hasHeightForWidth());
        flags_pl->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(flags_pl);


        horizontalLayout_3->addWidget(frame);

        frame_9 = new QFrame(other_flags_frame);
        frame_9->setObjectName("frame_9");
        sizePolicy1.setHeightForWidth(frame_9->sizePolicy().hasHeightForWidth());
        frame_9->setSizePolicy(sizePolicy1);
        frame_9->setFrameShape(QFrame::Shape::NoFrame);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_17 = new QVBoxLayout(frame_9);
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(frame_9);
        label_4->setObjectName("label_4");
        label_4->setFrameShape(QFrame::Shape::NoFrame);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_17->addWidget(label_4);

        flags_pr2 = new QCheckBox(frame_9);
        flags_pr2->setObjectName("flags_pr2");
        flags_pr2->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_pr2->sizePolicy().hasHeightForWidth());
        flags_pr2->setSizePolicy(sizePolicy1);

        verticalLayout_17->addWidget(flags_pr2);


        horizontalLayout_3->addWidget(frame_9);

        frame_10 = new QFrame(other_flags_frame);
        frame_10->setObjectName("frame_10");
        sizePolicy1.setHeightForWidth(frame_10->sizePolicy().hasHeightForWidth());
        frame_10->setSizePolicy(sizePolicy1);
        frame_10->setFrameShape(QFrame::Shape::NoFrame);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_18 = new QVBoxLayout(frame_10);
        verticalLayout_18->setSpacing(0);
        verticalLayout_18->setObjectName("verticalLayout_18");
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(frame_10);
        label_10->setObjectName("label_10");
        label_10->setFrameShape(QFrame::Shape::NoFrame);
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_18->addWidget(label_10);

        flags_pr1 = new QCheckBox(frame_10);
        flags_pr1->setObjectName("flags_pr1");
        flags_pr1->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_pr1->sizePolicy().hasHeightForWidth());
        flags_pr1->setSizePolicy(sizePolicy1);

        verticalLayout_18->addWidget(flags_pr1);


        horizontalLayout_3->addWidget(frame_10);

        frame_11 = new QFrame(other_flags_frame);
        frame_11->setObjectName("frame_11");
        sizePolicy1.setHeightForWidth(frame_11->sizePolicy().hasHeightForWidth());
        frame_11->setSizePolicy(sizePolicy1);
        frame_11->setFrameShape(QFrame::Shape::NoFrame);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_19 = new QVBoxLayout(frame_11);
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName("verticalLayout_19");
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(frame_11);
        label_12->setObjectName("label_12");
        label_12->setFrameShape(QFrame::Shape::NoFrame);
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_19->addWidget(label_12);

        flags_pr0 = new QCheckBox(frame_11);
        flags_pr0->setObjectName("flags_pr0");
        flags_pr0->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_pr0->sizePolicy().hasHeightForWidth());
        flags_pr0->setSizePolicy(sizePolicy1);

        verticalLayout_19->addWidget(flags_pr0);


        horizontalLayout_3->addWidget(frame_11);

        frame_12 = new QFrame(other_flags_frame);
        frame_12->setObjectName("frame_12");
        sizePolicy1.setHeightForWidth(frame_12->sizePolicy().hasHeightForWidth());
        frame_12->setSizePolicy(sizePolicy1);
        frame_12->setFrameShape(QFrame::Shape::NoFrame);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_20 = new QVBoxLayout(frame_12);
        verticalLayout_20->setSpacing(0);
        verticalLayout_20->setObjectName("verticalLayout_20");
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(frame_12);
        label_6->setObjectName("label_6");
        label_6->setFrameShape(QFrame::Shape::NoFrame);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_20->addWidget(label_6);

        flags_n = new QCheckBox(frame_12);
        flags_n->setObjectName("flags_n");
        flags_n->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_n->sizePolicy().hasHeightForWidth());
        flags_n->setSizePolicy(sizePolicy1);
        flags_n->setChecked(true);

        verticalLayout_20->addWidget(flags_n);


        horizontalLayout_3->addWidget(frame_12);

        frame_13 = new QFrame(other_flags_frame);
        frame_13->setObjectName("frame_13");
        sizePolicy1.setHeightForWidth(frame_13->sizePolicy().hasHeightForWidth());
        frame_13->setSizePolicy(sizePolicy1);
        frame_13->setFrameShape(QFrame::Shape::NoFrame);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_21 = new QVBoxLayout(frame_13);
        verticalLayout_21->setSpacing(0);
        verticalLayout_21->setObjectName("verticalLayout_21");
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(frame_13);
        label_8->setObjectName("label_8");
        label_8->setFrameShape(QFrame::Shape::NoFrame);
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_21->addWidget(label_8);

        flags_z = new QCheckBox(frame_13);
        flags_z->setObjectName("flags_z");
        flags_z->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_z->sizePolicy().hasHeightForWidth());
        flags_z->setSizePolicy(sizePolicy1);

        verticalLayout_21->addWidget(flags_z);


        horizontalLayout_3->addWidget(frame_13);

        frame_14 = new QFrame(other_flags_frame);
        frame_14->setObjectName("frame_14");
        sizePolicy1.setHeightForWidth(frame_14->sizePolicy().hasHeightForWidth());
        frame_14->setSizePolicy(sizePolicy1);
        frame_14->setFrameShape(QFrame::Shape::NoFrame);
        frame_14->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_22 = new QVBoxLayout(frame_14);
        verticalLayout_22->setSpacing(0);
        verticalLayout_22->setObjectName("verticalLayout_22");
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(frame_14);
        label_14->setObjectName("label_14");
        label_14->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_22->addWidget(label_14);

        flags_p = new QCheckBox(frame_14);
        flags_p->setObjectName("flags_p");
        flags_p->setEnabled(false);
        sizePolicy1.setHeightForWidth(flags_p->sizePolicy().hasHeightForWidth());
        flags_p->setSizePolicy(sizePolicy1);

        verticalLayout_22->addWidget(flags_p);


        horizontalLayout_3->addWidget(frame_14);

        horizontalSpacer_10 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        verticalLayout->addWidget(other_flags_frame);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(Flags);

        QMetaObject::connectSlotsByName(Flags);
    } // setupUi

    void retranslateUi(QWidget *Flags)
    {
        Flags->setWindowTitle(QCoreApplication::translate("Flags", "Form", nullptr));
        flag_negative->setText(QString());
        flag_zero->setText(QString());
        flag_positive->setText(QString());
        frame->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_2->setText(QCoreApplication::translate("Flags", "PL", nullptr));
        label_2->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_pl->setText(QCoreApplication::translate("Flags", "0", nullptr));
        frame_9->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_4->setText(QCoreApplication::translate("Flags", "PR2", nullptr));
        label_4->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_pr2->setText(QCoreApplication::translate("Flags", "0", nullptr));
        frame_10->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_10->setText(QCoreApplication::translate("Flags", "PR1", nullptr));
        label_10->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_pr1->setText(QCoreApplication::translate("Flags", "0", nullptr));
        frame_11->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_12->setText(QCoreApplication::translate("Flags", "PR0", nullptr));
        label_12->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_pr0->setText(QCoreApplication::translate("Flags", "0", nullptr));
        frame_12->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_6->setText(QCoreApplication::translate("Flags", "N", nullptr));
        label_6->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_n->setText(QCoreApplication::translate("Flags", "1", nullptr));
        frame_13->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_8->setText(QCoreApplication::translate("Flags", "Z", nullptr));
        label_8->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_z->setText(QCoreApplication::translate("Flags", "0", nullptr));
        frame_14->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-card", nullptr)));
        label_14->setText(QCoreApplication::translate("Flags", "P", nullptr));
        label_14->setProperty("type", QVariant(QCoreApplication::translate("Flags", "flags-other-name", nullptr)));
        flags_p->setText(QCoreApplication::translate("Flags", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Flags: public Ui_Flags {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FLAGSQRBVAG_H
