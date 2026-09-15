/********************************************************************************
** Form generated from reading UI file 'aboutgXMNAf.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ABOUTGXMNAF_H
#define ABOUTGXMNAF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_app;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_app_icon;
    QHBoxLayout *horizontalLayout_6;
    QLabel *app_icon;
    QFrame *frame_app_info;
    QVBoxLayout *verticalLayout_2;
    QLabel *app_name;
    QLabel *app_desc;
    QLabel *app_ver;
    QFrame *frame_links;
    QVBoxLayout *verticalLayout_9;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_doc_ico;
    QVBoxLayout *verticalLayout_4;
    QLabel *docs_icon;
    QFrame *frame_doc_text;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_doc_title;
    QLabel *label_doc_desc;
    QFrame *frame_doc_link;
    QVBoxLayout *verticalLayout_12;
    QPushButton *docs_open;
    QFrame *frame_10;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_src_ico;
    QVBoxLayout *verticalLayout_5;
    QLabel *src_code_icon;
    QFrame *frame_src_text;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_src_title;
    QLabel *label_src_desc;
    QFrame *frame_src_link;
    QVBoxLayout *verticalLayout_11;
    QPushButton *src_code_open;
    QFrame *frame_13;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_dev_ico;
    QVBoxLayout *verticalLayout_7;
    QLabel *developer_icon;
    QFrame *frame_dev_text;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_dev_title;
    QLabel *label_dev_desc;
    QFrame *frame_dev_link;
    QVBoxLayout *verticalLayout_10;
    QPushButton *developer_profile_open;
    QFrame *frame_dev_info;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_dev_info;
    QFrame *frame_devi_text;
    QGridLayout *gridLayout;
    QLabel *qt_ver;
    QLabel *label_qt_ver;
    QLabel *label_cpp_ver;
    QSpacerItem *verticalSpacer;
    QLabel *cpp_ver;
    QLabel *label_lib_ver;
    QLabel *lib_ver;
    QFrame *frame_bottom;
    QHBoxLayout *horizontalLayout_5;
    QLabel *heart_icon;
    QHBoxLayout *horizontalLayout_7;
    QLabel *madeby;
    QPushButton *developer_profile_open2;
    QSpacerItem *horizontalSpacer;
    QPushButton *close_win;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(394, 476);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName("verticalLayout");
        frame_app = new QFrame(About);
        frame_app->setObjectName("frame_app");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_app->sizePolicy().hasHeightForWidth());
        frame_app->setSizePolicy(sizePolicy);
        frame_app->setFrameShape(QFrame::Shape::NoFrame);
        frame_app->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_app);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame_app_icon = new QFrame(frame_app);
        frame_app_icon->setObjectName("frame_app_icon");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_app_icon->sizePolicy().hasHeightForWidth());
        frame_app_icon->setSizePolicy(sizePolicy1);
        frame_app_icon->setFrameShape(QFrame::Shape::NoFrame);
        frame_app_icon->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_app_icon);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        app_icon = new QLabel(frame_app_icon);
        app_icon->setObjectName("app_icon");
        app_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_6->addWidget(app_icon);


        horizontalLayout->addWidget(frame_app_icon);

        frame_app_info = new QFrame(frame_app);
        frame_app_info->setObjectName("frame_app_info");
        frame_app_info->setFrameShape(QFrame::Shape::NoFrame);
        frame_app_info->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_app_info);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        app_name = new QLabel(frame_app_info);
        app_name->setObjectName("app_name");

        verticalLayout_2->addWidget(app_name);

        app_desc = new QLabel(frame_app_info);
        app_desc->setObjectName("app_desc");

        verticalLayout_2->addWidget(app_desc);

        app_ver = new QLabel(frame_app_info);
        app_ver->setObjectName("app_ver");

        verticalLayout_2->addWidget(app_ver);


        horizontalLayout->addWidget(frame_app_info);


        verticalLayout->addWidget(frame_app);

        frame_links = new QFrame(About);
        frame_links->setObjectName("frame_links");
        frame_links->setFrameShape(QFrame::Shape::NoFrame);
        frame_links->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_links);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        frame_7 = new QFrame(frame_links);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::NoFrame);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_7);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_doc_ico = new QFrame(frame_7);
        frame_doc_ico->setObjectName("frame_doc_ico");
        sizePolicy1.setHeightForWidth(frame_doc_ico->sizePolicy().hasHeightForWidth());
        frame_doc_ico->setSizePolicy(sizePolicy1);
        frame_doc_ico->setFrameShape(QFrame::Shape::NoFrame);
        frame_doc_ico->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_doc_ico);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        docs_icon = new QLabel(frame_doc_ico);
        docs_icon->setObjectName("docs_icon");
        docs_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(docs_icon);


        horizontalLayout_2->addWidget(frame_doc_ico);

        frame_doc_text = new QFrame(frame_7);
        frame_doc_text->setObjectName("frame_doc_text");
        frame_doc_text->setFrameShape(QFrame::Shape::NoFrame);
        frame_doc_text->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_doc_text);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_doc_title = new QLabel(frame_doc_text);
        label_doc_title->setObjectName("label_doc_title");

        verticalLayout_3->addWidget(label_doc_title);

        label_doc_desc = new QLabel(frame_doc_text);
        label_doc_desc->setObjectName("label_doc_desc");

        verticalLayout_3->addWidget(label_doc_desc);


        horizontalLayout_2->addWidget(frame_doc_text);

        frame_doc_link = new QFrame(frame_7);
        frame_doc_link->setObjectName("frame_doc_link");
        sizePolicy1.setHeightForWidth(frame_doc_link->sizePolicy().hasHeightForWidth());
        frame_doc_link->setSizePolicy(sizePolicy1);
        frame_doc_link->setFrameShape(QFrame::Shape::NoFrame);
        frame_doc_link->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_12 = new QVBoxLayout(frame_doc_link);
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        docs_open = new QPushButton(frame_doc_link);
        docs_open->setObjectName("docs_open");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(docs_open->sizePolicy().hasHeightForWidth());
        docs_open->setSizePolicy(sizePolicy2);
        docs_open->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        docs_open->setIconSize(QSize(20, 20));

        verticalLayout_12->addWidget(docs_open);


        horizontalLayout_2->addWidget(frame_doc_link);


        verticalLayout_9->addWidget(frame_7);

        frame_10 = new QFrame(frame_links);
        frame_10->setObjectName("frame_10");
        frame_10->setFrameShape(QFrame::Shape::NoFrame);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_10);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_src_ico = new QFrame(frame_10);
        frame_src_ico->setObjectName("frame_src_ico");
        sizePolicy1.setHeightForWidth(frame_src_ico->sizePolicy().hasHeightForWidth());
        frame_src_ico->setSizePolicy(sizePolicy1);
        frame_src_ico->setFrameShape(QFrame::Shape::NoFrame);
        frame_src_ico->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_src_ico);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        src_code_icon = new QLabel(frame_src_ico);
        src_code_icon->setObjectName("src_code_icon");
        src_code_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(src_code_icon);


        horizontalLayout_3->addWidget(frame_src_ico);

        frame_src_text = new QFrame(frame_10);
        frame_src_text->setObjectName("frame_src_text");
        frame_src_text->setFrameShape(QFrame::Shape::NoFrame);
        frame_src_text->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_src_text);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_src_title = new QLabel(frame_src_text);
        label_src_title->setObjectName("label_src_title");

        verticalLayout_6->addWidget(label_src_title);

        label_src_desc = new QLabel(frame_src_text);
        label_src_desc->setObjectName("label_src_desc");

        verticalLayout_6->addWidget(label_src_desc);


        horizontalLayout_3->addWidget(frame_src_text);

        frame_src_link = new QFrame(frame_10);
        frame_src_link->setObjectName("frame_src_link");
        sizePolicy1.setHeightForWidth(frame_src_link->sizePolicy().hasHeightForWidth());
        frame_src_link->setSizePolicy(sizePolicy1);
        frame_src_link->setFrameShape(QFrame::Shape::NoFrame);
        frame_src_link->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_11 = new QVBoxLayout(frame_src_link);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        src_code_open = new QPushButton(frame_src_link);
        src_code_open->setObjectName("src_code_open");
        sizePolicy2.setHeightForWidth(src_code_open->sizePolicy().hasHeightForWidth());
        src_code_open->setSizePolicy(sizePolicy2);
        src_code_open->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        src_code_open->setIconSize(QSize(20, 20));

        verticalLayout_11->addWidget(src_code_open);


        horizontalLayout_3->addWidget(frame_src_link);


        verticalLayout_9->addWidget(frame_10);

        frame_13 = new QFrame(frame_links);
        frame_13->setObjectName("frame_13");
        frame_13->setFrameShape(QFrame::Shape::NoFrame);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_13);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        frame_dev_ico = new QFrame(frame_13);
        frame_dev_ico->setObjectName("frame_dev_ico");
        sizePolicy1.setHeightForWidth(frame_dev_ico->sizePolicy().hasHeightForWidth());
        frame_dev_ico->setSizePolicy(sizePolicy1);
        frame_dev_ico->setFrameShape(QFrame::Shape::NoFrame);
        frame_dev_ico->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_dev_ico);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        developer_icon = new QLabel(frame_dev_ico);
        developer_icon->setObjectName("developer_icon");
        developer_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(developer_icon);


        horizontalLayout_4->addWidget(frame_dev_ico);

        frame_dev_text = new QFrame(frame_13);
        frame_dev_text->setObjectName("frame_dev_text");
        frame_dev_text->setFrameShape(QFrame::Shape::NoFrame);
        frame_dev_text->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_dev_text);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_dev_title = new QLabel(frame_dev_text);
        label_dev_title->setObjectName("label_dev_title");

        verticalLayout_8->addWidget(label_dev_title);

        label_dev_desc = new QLabel(frame_dev_text);
        label_dev_desc->setObjectName("label_dev_desc");

        verticalLayout_8->addWidget(label_dev_desc);


        horizontalLayout_4->addWidget(frame_dev_text);

        frame_dev_link = new QFrame(frame_13);
        frame_dev_link->setObjectName("frame_dev_link");
        sizePolicy1.setHeightForWidth(frame_dev_link->sizePolicy().hasHeightForWidth());
        frame_dev_link->setSizePolicy(sizePolicy1);
        frame_dev_link->setFrameShape(QFrame::Shape::NoFrame);
        frame_dev_link->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_dev_link);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        developer_profile_open = new QPushButton(frame_dev_link);
        developer_profile_open->setObjectName("developer_profile_open");
        sizePolicy2.setHeightForWidth(developer_profile_open->sizePolicy().hasHeightForWidth());
        developer_profile_open->setSizePolicy(sizePolicy2);
        developer_profile_open->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        developer_profile_open->setIconSize(QSize(20, 20));

        verticalLayout_10->addWidget(developer_profile_open);


        horizontalLayout_4->addWidget(frame_dev_link);


        verticalLayout_9->addWidget(frame_13);


        verticalLayout->addWidget(frame_links);

        frame_dev_info = new QFrame(About);
        frame_dev_info->setObjectName("frame_dev_info");
        frame_dev_info->setFrameShape(QFrame::Shape::NoFrame);
        frame_dev_info->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_13 = new QVBoxLayout(frame_dev_info);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_dev_info = new QLabel(frame_dev_info);
        label_dev_info->setObjectName("label_dev_info");
        sizePolicy.setHeightForWidth(label_dev_info->sizePolicy().hasHeightForWidth());
        label_dev_info->setSizePolicy(sizePolicy);

        verticalLayout_13->addWidget(label_dev_info);

        frame_devi_text = new QFrame(frame_dev_info);
        frame_devi_text->setObjectName("frame_devi_text");
        frame_devi_text->setFrameShape(QFrame::Shape::NoFrame);
        frame_devi_text->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame_devi_text);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        qt_ver = new QLabel(frame_devi_text);
        qt_ver->setObjectName("qt_ver");

        gridLayout->addWidget(qt_ver, 0, 1, 1, 1);

        label_qt_ver = new QLabel(frame_devi_text);
        label_qt_ver->setObjectName("label_qt_ver");

        gridLayout->addWidget(label_qt_ver, 0, 0, 1, 1);

        label_cpp_ver = new QLabel(frame_devi_text);
        label_cpp_ver->setObjectName("label_cpp_ver");

        gridLayout->addWidget(label_cpp_ver, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(0, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 2);

        cpp_ver = new QLabel(frame_devi_text);
        cpp_ver->setObjectName("cpp_ver");

        gridLayout->addWidget(cpp_ver, 1, 1, 1, 1);

        label_lib_ver = new QLabel(frame_devi_text);
        label_lib_ver->setObjectName("label_lib_ver");

        gridLayout->addWidget(label_lib_ver, 2, 0, 1, 1);

        lib_ver = new QLabel(frame_devi_text);
        lib_ver->setObjectName("lib_ver");

        gridLayout->addWidget(lib_ver, 2, 1, 1, 1);


        verticalLayout_13->addWidget(frame_devi_text);


        verticalLayout->addWidget(frame_dev_info);

        frame_bottom = new QFrame(About);
        frame_bottom->setObjectName("frame_bottom");
        sizePolicy.setHeightForWidth(frame_bottom->sizePolicy().hasHeightForWidth());
        frame_bottom->setSizePolicy(sizePolicy);
        frame_bottom->setFrameShape(QFrame::Shape::NoFrame);
        frame_bottom->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_bottom);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        heart_icon = new QLabel(frame_bottom);
        heart_icon->setObjectName("heart_icon");
        sizePolicy1.setHeightForWidth(heart_icon->sizePolicy().hasHeightForWidth());
        heart_icon->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(heart_icon);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        madeby = new QLabel(frame_bottom);
        madeby->setObjectName("madeby");

        horizontalLayout_7->addWidget(madeby);

        developer_profile_open2 = new QPushButton(frame_bottom);
        developer_profile_open2->setObjectName("developer_profile_open2");

        horizontalLayout_7->addWidget(developer_profile_open2);


        horizontalLayout_5->addLayout(horizontalLayout_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        close_win = new QPushButton(frame_bottom);
        close_win->setObjectName("close_win");

        horizontalLayout_5->addWidget(close_win);


        verticalLayout->addWidget(frame_bottom);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Dialog", nullptr));
        app_icon->setText(QString());
        app_name->setText(QCoreApplication::translate("About", "LC3kit IDE", nullptr));
        app_desc->setText(QCoreApplication::translate("About", "An integrated environment for LC3 architecture", nullptr));
        app_ver->setText(QCoreApplication::translate("About", "Version 1.0.0", nullptr));
        frame_7->setProperty("type", QVariant(QCoreApplication::translate("About", "link-frame", nullptr)));
        docs_icon->setText(QString());
        label_doc_title->setText(QCoreApplication::translate("About", "Documentation", nullptr));
        label_doc_desc->setText(QCoreApplication::translate("About", "Read the documentation and guides.", nullptr));
        docs_open->setText(QString());
        frame_10->setProperty("type", QVariant(QCoreApplication::translate("About", "link-frame", nullptr)));
        src_code_icon->setText(QString());
        label_src_title->setText(QCoreApplication::translate("About", "Source Code", nullptr));
        label_src_desc->setText(QCoreApplication::translate("About", "View the project on GitHub.", nullptr));
        src_code_open->setText(QString());
        frame_13->setProperty("type", QVariant(QCoreApplication::translate("About", "link-frame", nullptr)));
        developer_icon->setText(QString());
        label_dev_title->setText(QCoreApplication::translate("About", "Developer", nullptr));
        label_dev_desc->setText(QCoreApplication::translate("About", "Visit the developer's profile.", nullptr));
        developer_profile_open->setText(QString());
        label_dev_info->setText(QCoreApplication::translate("About", "Developement Information", nullptr));
        qt_ver->setText(QCoreApplication::translate("About", "6.7.2", nullptr));
        label_qt_ver->setText(QCoreApplication::translate("About", "Qt Version", nullptr));
        label_cpp_ver->setText(QCoreApplication::translate("About", "C++ Version", nullptr));
        cpp_ver->setText(QCoreApplication::translate("About", "C++23", nullptr));
        label_lib_ver->setText(QCoreApplication::translate("About", "LC3kit core library Version", nullptr));
        lib_ver->setText(QCoreApplication::translate("About", "0.0.0", nullptr));
        heart_icon->setText(QString());
        madeby->setText(QCoreApplication::translate("About", "Made with love by", nullptr));
        developer_profile_open2->setText(QCoreApplication::translate("About", "0xbad4", nullptr));
        close_win->setText(QCoreApplication::translate("About", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ABOUTGXMNAF_H
