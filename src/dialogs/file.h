#pragma once

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>


namespace lc3kit::ide::filed
{
    inline static const QString PICKER_FILTER_DEF = "LC-3 Assembly (*.asm);;All Files (*)";

    inline QString get_save_file(QWidget* parentw = nullptr, const QString& root = QString(), QString fl = PICKER_FILTER_DEF) {
        static QString last_save_dir = QDir::homePath();

        QString start_dir = !root.isEmpty() ? root : last_save_dir;

        QString chosen = QFileDialog::getSaveFileName(
            parentw,
            "Save File",
            start_dir,
            fl
        );

        if (!chosen.isEmpty()) {
            last_save_dir = QFileInfo(chosen).absolutePath();
        }

        return chosen;
    }

    inline QString get_open_file(QWidget* parentw = nullptr, const QString& root = QString(), QString fl = PICKER_FILTER_DEF) {
        static QString last_open_dir = QDir::homePath();

        QString start_dir = !root.isEmpty() ? root : last_open_dir;

        QString chosen = QFileDialog::getOpenFileName(
            parentw,
            "Open File",
            start_dir,
            fl
        );

        if (!chosen.isEmpty()) {
            last_open_dir = QFileInfo(chosen).absolutePath();
        }

        return chosen;
    }
    
} // namespace lc3kit::ide
