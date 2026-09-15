#pragma once
#include <QMessageBox>
#include <QInputDialog>

namespace lc3kit::ide {
    namespace dialog {

        inline QMessageBox::StandardButton ask(const QString& title, const QString& msg, QWidget*parent=nullptr, bool cancel=false) {
            QMessageBox box(QMessageBox::Question, title, msg,
                QMessageBox::Yes | QMessageBox::No | (cancel ? QMessageBox::Cancel : QMessageBox::NoButton),
                parent, Qt::Dialog | Qt::FramelessWindowHint);
            box.setDefaultButton(QMessageBox::Yes);
            box.setIcon(QMessageBox::Icon::NoIcon);
            box.exec();
            return static_cast<QMessageBox::StandardButton>(box.standardButton(box.clickedButton()));
        }

        inline QString pick(const QString& title, const QString& msg, const QStringList& items, bool* ok = nullptr) {
            return QInputDialog::getItem(nullptr, title, msg, items, 0, false, ok,
                Qt::Dialog | Qt::FramelessWindowHint);
        }

        inline int number(const QString& title, const QString& msg, int value = 0, int min = 0, int max = sizeof(int), int decimals = 0, bool* ok = nullptr) {
            return QInputDialog::getInt(nullptr, title, msg, value, min, max, decimals, ok,
                Qt::Dialog | Qt::FramelessWindowHint);
        }
    }

} // namespace lc3kit::ide