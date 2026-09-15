#pragma once
#include <QMetaType>
#include <QDebug>
#include <QFileInfo>
#include <QLayout>
#include <QKeyEvent>
#include <QObject>
#include <QThread>
#include <QHeaderView>
#include <QString>
#include <QBrush>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "themes/tman.h"

#include <lc3kit/vm>
#include <lc3kit/asm>


namespace lc3kit::ide {
    using vm_ptr_t = vm::VM*;
    using asm_ptr_t = lasm::Asm*;

    inline QString format_binary(std_word_t val) {
        QString b = QString::number(val, 2).rightJustified(16, '0');
        // insert spaces every 4 bits for readability: 0000 0000 0000 0000
        return b.left(4) + ' ' + b.mid(4,4) + ' ' + b.mid(8,4) + ' ' + b.mid(12,4);
    }

    inline QString format_hex(std_word_t val) {
        return QString("0x") + QString("%1").arg(val,  4, 16, QChar('0')).toUpper();
    }

    // by convention, addr is stored at col 0
    inline std_word_t item_addr(QTreeWidgetItem* item) {
        return (std_word_t)item->data(0, Qt::UserRole).toUInt();
    }

    inline void mark_last_changed(QTreeWidgetItem*& previous, QTreeWidgetItem* current) {
        if (previous) {
            previous->setIcon(0, QIcon());
        }

        previous = current;
        
        if (current) {
            current->setIcon(0, ICON("item-marker"));
        }
    }

    inline QByteArray export_section(const lasm::section& section) {
        QByteArray out;

        std_word_t origin = section.origin;

        out.append(static_cast<char>(origin >> 8));
        out.append(static_cast<char>(origin & 0xFF));

        for (std_word_t word : section.words) {
            out.append(static_cast<char>(word >> 8));
            out.append(static_cast<char>(word & 0xFF));
        }

        return out;
    }

    inline QByteArray dump_sections(const lasm::sections_t& sections) {
        QByteArray out;

        for (const auto& section : sections) {
            out.append(export_section(section));
        }

        return out;
    }

    inline QString printable_char(std_word_t value) {
        return (value >= 0x20 && value <= 0x7E)
            ? QString(QChar(value))
            : QString();
    }

    inline bool is_asm_file(const QString& fp) {
        static const QSet<QString> asm_exts = {
            "asm",
            "s",
            "S",
            "inc"
        };

        return asm_exts.contains(QFileInfo(fp).suffix());
    }
} // namespace lc3kit::ide
