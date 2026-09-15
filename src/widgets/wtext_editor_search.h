/********************************************************************************
** Form generated from reading UI file 'text-editor-search-popupZIyGtO.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TEXT_2D_EDITOR_2D_SEARCH_2D_POPUPZIYGTO_H
#define TEXT_2D_EDITOR_2D_SEARCH_2D_POPUPZIYGTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TESearch
{
public:
    QGridLayout *gridLayout;
    QPushButton *search_replace_current;
    QLineEdit *search_replacement;
    QLineEdit *search_term;
    QPushButton *search_previous;
    QHBoxLayout *horizontalLayout;
    QLabel *search_current_label;
    QLabel *label_2;
    QLabel *search_count;
    QSpacerItem *horizontalSpacer;
    QPushButton *search_close;
    QPushButton *search_replace_all;
    QPushButton *search_next;

    void setupUi(QWidget *TESearch)
    {
        if (TESearch->objectName().isEmpty())
            TESearch->setObjectName("TESearch");
        TESearch->resize(298, 72);
        TESearch->setStyleSheet(QString::fromUtf8("#TESearch {\n"
"	background-color: #262626;\n"
"    border: 1px solid #343434;\n"
"    border-radius: 2px;\n"
"}"));
        gridLayout = new QGridLayout(TESearch);
        gridLayout->setObjectName("gridLayout");
        search_replace_current = new QPushButton(TESearch);
        search_replace_current->setObjectName("search_replace_current");
        search_replace_current->setMaximumSize(QSize(30, 16777215));
        search_replace_current->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        search_replace_current->setIconSize(QSize(20, 20));

        gridLayout->addWidget(search_replace_current, 1, 2, 1, 1);

        search_replacement = new QLineEdit(TESearch);
        search_replacement->setObjectName("search_replacement");
        search_replacement->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(search_replacement, 1, 0, 1, 1);

        search_term = new QLineEdit(TESearch);
        search_term->setObjectName("search_term");
        search_term->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(search_term, 0, 0, 1, 1);

        search_previous = new QPushButton(TESearch);
        search_previous->setObjectName("search_previous");
        search_previous->setMaximumSize(QSize(30, 16777215));
        search_previous->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        search_previous->setIconSize(QSize(20, 20));

        gridLayout->addWidget(search_previous, 0, 6, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        search_current_label = new QLabel(TESearch);
        search_current_label->setObjectName("search_current_label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(search_current_label->sizePolicy().hasHeightForWidth());
        search_current_label->setSizePolicy(sizePolicy);
        search_current_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(search_current_label);

        label_2 = new QLabel(TESearch);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_2);

        search_count = new QLabel(TESearch);
        search_count->setObjectName("search_count");
        sizePolicy.setHeightForWidth(search_count->sizePolicy().hasHeightForWidth());
        search_count->setSizePolicy(sizePolicy);
        search_count->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(search_count);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 2);

        search_close = new QPushButton(TESearch);
        search_close->setObjectName("search_close");
        search_close->setMaximumSize(QSize(30, 16777215));
        search_close->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        search_close->setIconSize(QSize(20, 20));

        gridLayout->addWidget(search_close, 0, 8, 1, 1);

        search_replace_all = new QPushButton(TESearch);
        search_replace_all->setObjectName("search_replace_all");
        search_replace_all->setMaximumSize(QSize(30, 16777215));
        search_replace_all->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        search_replace_all->setIconSize(QSize(20, 20));

        gridLayout->addWidget(search_replace_all, 1, 3, 1, 1);

        search_next = new QPushButton(TESearch);
        search_next->setObjectName("search_next");
        search_next->setMaximumSize(QSize(30, 16777215));
        search_next->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        search_next->setIconSize(QSize(20, 20));

        gridLayout->addWidget(search_next, 0, 7, 1, 1);


        retranslateUi(TESearch);

        QMetaObject::connectSlotsByName(TESearch);
    } // setupUi

    void retranslateUi(QWidget *TESearch)
    {
        TESearch->setWindowTitle(QCoreApplication::translate("TESearch", "Form", nullptr));
#if QT_CONFIG(tooltip)
        search_replace_current->setToolTip(QCoreApplication::translate("TESearch", "Replace", nullptr));
#endif // QT_CONFIG(tooltip)
        search_replace_current->setText(QString());
        search_replacement->setPlaceholderText(QCoreApplication::translate("TESearch", "Replace", nullptr));
        search_term->setPlaceholderText(QCoreApplication::translate("TESearch", "Find", nullptr));
        search_previous->setText(QString());
        search_current_label->setText(QCoreApplication::translate("TESearch", "1", nullptr));
        label_2->setText(QCoreApplication::translate("TESearch", "/", nullptr));
        search_count->setText(QCoreApplication::translate("TESearch", "16", nullptr));
        search_close->setText(QString());
#if QT_CONFIG(tooltip)
        search_replace_all->setToolTip(QCoreApplication::translate("TESearch", "Replace All", nullptr));
#endif // QT_CONFIG(tooltip)
        search_replace_all->setText(QString());
        search_next->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TESearch: public Ui_TESearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TEXT_2D_EDITOR_2D_SEARCH_2D_POPUPZIYGTO_H
