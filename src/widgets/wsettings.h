/********************************************************************************
** Form generated from reading UI file 'settingsqXVWEY.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGSQXVWEY_H
#define SETTINGSQXVWEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *view_all_mem;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *ext_en;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *asm_on_save;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *asm_on_run;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *theme_opts;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName("Settings");
        Settings->resize(360, 344);
        Settings->setStyleSheet(QString::fromUtf8("#Settings {\n"
"	margin: 4px;\n"
"}"));
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(Settings);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 360, 344));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        view_all_mem = new QCheckBox(frame);
        view_all_mem->setObjectName("view_all_mem");
        sizePolicy1.setHeightForWidth(view_all_mem->sizePolicy().hasHeightForWidth());
        view_all_mem->setSizePolicy(sizePolicy1);
        view_all_mem->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(view_all_mem);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName("frame_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_2);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        ext_en = new QCheckBox(frame_2);
        ext_en->setObjectName("ext_en");
        sizePolicy1.setHeightForWidth(ext_en->sizePolicy().hasHeightForWidth());
        ext_en->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(ext_en);


        horizontalLayout_7->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(frame_2);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName("frame_3");
        sizePolicy2.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy2);
        frame_3->setFrameShape(QFrame::Shape::NoFrame);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_3);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        asm_on_save = new QCheckBox(frame_3);
        asm_on_save->setObjectName("asm_on_save");
        sizePolicy1.setHeightForWidth(asm_on_save->sizePolicy().hasHeightForWidth());
        asm_on_save->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(asm_on_save);


        horizontalLayout_8->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(frame_3);

        frame_4 = new QFrame(scrollAreaWidgetContents);
        frame_4->setObjectName("frame_4");
        sizePolicy2.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy2);
        frame_4->setFrameShape(QFrame::Shape::NoFrame);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_4);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(label_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        asm_on_run = new QCheckBox(frame_4);
        asm_on_run->setObjectName("asm_on_run");
        sizePolicy1.setHeightForWidth(asm_on_run->sizePolicy().hasHeightForWidth());
        asm_on_run->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(asm_on_run);


        horizontalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(frame_4);

        frame_5 = new QFrame(scrollAreaWidgetContents);
        frame_5->setObjectName("frame_5");
        sizePolicy2.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy2);
        frame_5->setFrameShape(QFrame::Shape::NoFrame);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_10 = new QHBoxLayout(frame_5);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(frame_5);
        label_6->setObjectName("label_6");
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(label_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_5 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        theme_opts = new QComboBox(frame_5);
        theme_opts->setObjectName("theme_opts");
        sizePolicy.setHeightForWidth(theme_opts->sizePolicy().hasHeightForWidth());
        theme_opts->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(theme_opts);


        horizontalLayout_10->addLayout(horizontalLayout_11);


        verticalLayout_2->addWidget(frame_5);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Form", nullptr));
        frame->setProperty("type", QVariant(QCoreApplication::translate("Settings", "settings-item", nullptr)));
        label_2->setText(QCoreApplication::translate("Settings", "Show All Memory Addresses", nullptr));
        view_all_mem->setText(QString());
        view_all_mem->setProperty("type", QVariant(QCoreApplication::translate("Settings", "toggle", nullptr)));
        frame_2->setProperty("type", QVariant(QCoreApplication::translate("Settings", "settings-item", nullptr)));
        label_3->setText(QCoreApplication::translate("Settings", "Enable Daedalus Extension", nullptr));
        ext_en->setText(QString());
        ext_en->setProperty("type", QVariant(QCoreApplication::translate("Settings", "toggle", nullptr)));
        frame_3->setProperty("type", QVariant(QCoreApplication::translate("Settings", "settings-item", nullptr)));
        label_4->setText(QCoreApplication::translate("Settings", "Assemble Automatically On Save", nullptr));
        asm_on_save->setText(QString());
        asm_on_save->setProperty("type", QVariant(QCoreApplication::translate("Settings", "toggle", nullptr)));
        frame_4->setProperty("type", QVariant(QCoreApplication::translate("Settings", "settings-item", nullptr)));
        label_5->setText(QCoreApplication::translate("Settings", "Assemble Before Every Run", nullptr));
        asm_on_run->setText(QString());
        asm_on_run->setProperty("type", QVariant(QCoreApplication::translate("Settings", "toggle", nullptr)));
        frame_5->setProperty("type", QVariant(QCoreApplication::translate("Settings", "settings-item", nullptr)));
        label_6->setText(QCoreApplication::translate("Settings", "Application Theme", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTINGSQXVWEY_H
