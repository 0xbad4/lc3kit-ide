/********************************************************************************
** Form generated from reading UI file 'default-tabxeIHkw.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DEFAULT_2D_TABXEIHKW_H
#define DEFAULT_2D_TABXEIHKW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DefaultTab
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *new_file_shortcut;
    QLabel *open_file;
    QSpacerItem *horizontalSpacer_3;
    QLabel *open_file_shortcut;
    QLabel *new_file;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *file_icon;

    void setupUi(QWidget *DefaultTab)
    {
        if (DefaultTab->objectName().isEmpty())
            DefaultTab->setObjectName("DefaultTab");
        DefaultTab->resize(745, 471);
        gridLayout = new QGridLayout(DefaultTab);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(273, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 207, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(274, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        frame = new QFrame(DefaultTab);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        new_file_shortcut = new QLabel(frame);
        new_file_shortcut->setObjectName("new_file_shortcut");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(new_file_shortcut->sizePolicy().hasHeightForWidth());
        new_file_shortcut->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(new_file_shortcut, 1, 2, 1, 1);

        open_file = new QLabel(frame);
        open_file->setObjectName("open_file");
        sizePolicy.setHeightForWidth(open_file->sizePolicy().hasHeightForWidth());
        open_file->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(open_file, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        open_file_shortcut = new QLabel(frame);
        open_file_shortcut->setObjectName("open_file_shortcut");
        sizePolicy.setHeightForWidth(open_file_shortcut->sizePolicy().hasHeightForWidth());
        open_file_shortcut->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(open_file_shortcut, 3, 2, 1, 1);

        new_file = new QLabel(frame);
        new_file->setObjectName("new_file");
        sizePolicy.setHeightForWidth(new_file->sizePolicy().hasHeightForWidth());
        new_file->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(new_file, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 3, 1, 1);


        gridLayout->addWidget(frame, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 206, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        file_icon = new QLabel(DefaultTab);
        file_icon->setObjectName("file_icon");
        file_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(file_icon, 1, 1, 1, 1);


        retranslateUi(DefaultTab);

        QMetaObject::connectSlotsByName(DefaultTab);
    } // setupUi

    void retranslateUi(QWidget *DefaultTab)
    {
        DefaultTab->setWindowTitle(QCoreApplication::translate("DefaultTab", "Form", nullptr));
        new_file_shortcut->setText(QCoreApplication::translate("DefaultTab", "Ctrl+N", nullptr));
        open_file->setText(QCoreApplication::translate("DefaultTab", "Open Existing File", nullptr));
        open_file_shortcut->setText(QCoreApplication::translate("DefaultTab", "Ctrl+O", nullptr));
        new_file->setText(QCoreApplication::translate("DefaultTab", "Create New File", nullptr));
        file_icon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DefaultTab: public Ui_DefaultTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEFAULT_2D_TABXEIHKW_H
