#pragma once

#include <QObject>
#include <QTextStream>
#include <QString>

#include "utils/logger.h"
#include "dialogs/file.h"

namespace lc3kit::ide {
    class FileHandler : public QObject {
        Q_OBJECT

        public:
            inline static const QString NAME = "FileHandler";

            explicit FileHandler(QObject* parent = nullptr) : QObject(parent) {}

            explicit FileHandler(const QString& path, QObject* parent = nullptr) : QObject(parent), m_path(path) {}

            bool    has_path()  const { return !m_path.isEmpty(); }
            QString path()      const { return m_path; }
            QString filename()  const {
                return m_path.isEmpty() ? "untitled" : QFileInfo(m_path).fileName();
            }

            void set_path(const QString& path) { m_path = path; }

            // read entire file content
            QString read() {
                if (m_path.isEmpty()) {
                    qDebug() << NAME << ": read() called for new untitled file — returning empty string";
                    return {};
                }

                qDebug() << NAME << ": reading file from disk"
                         << "path =" << m_path;

                QFile f(m_path);

                if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qWarning() << NAME << ": failed to open file for reading"
                               << "path =" << m_path
                               << "error =" << f.errorString();
                    DLERROR(QString("Cannot open '%1': %2").arg(m_path, f.errorString()), NAME);
                    return {};
                }

                QTextStream s(&f);
                s.setEncoding(QStringConverter::Utf8);
                QString content = s.readAll();

                qInfo() << NAME << ": file read successfully"
                        << "path =" << m_path
                        << "size =" << content.size() << "characters";

                return content;
            }

            // write content to disk.
            // if no path: show blocking QFileDialog — return false if user cancels.
            bool write(const QString& content, QWidget* dialog_parent = nullptr) {
                if (!has_path()) {
                    qDebug() << NAME << ": write() called without path — showing file save dialog";
                    QString chosen = filed::get_save_file(dialog_parent);

                    if (chosen.isEmpty()) {
                        qDebug() << NAME << ": file save dialog cancelled by user";
                        DLWARN("Save cancelled — no path selected", NAME);
                        return false;
                    }

                    m_path = chosen;
                    qDebug() << NAME << ": user selected save path"
                             << "path =" << m_path;
                }

                qDebug() << NAME << ": writing file to disk"
                         << "path =" << m_path
                         << "size =" << content.size() << "characters";

                QFile f(m_path);
                
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                    qWarning() << NAME << ": failed to open file for writing"
                               << "path =" << m_path
                               << "error =" << f.errorString();
                    DLERROR(
                        QString("Cannot write '%1': %2").arg(m_path, f.errorString()),
                        NAME);
                    return false;
                }

                QTextStream s(&f);
                s.setEncoding(QStringConverter::Utf8);
                s << content;

                qInfo() << NAME << ": file written successfully"
                        << "path =" << m_path
                        << "bytes_written =" << f.pos();

                DLLOG(QString("Saved: %1").arg(m_path), NAME);
                emit content_saved(m_path);
                return true;
            }

            // write as: always prompt for a new path, does not change m_path on cancel
            bool write_as(const QString& content, QWidget* dialog_parent = nullptr) {
                qDebug() << NAME << ": write_as() called — showing file save dialog";
                QString chosen = filed::get_save_file(dialog_parent);
                
                if (chosen.isEmpty()) {
                    qDebug() << NAME << ": save as dialog cancelled by user";
                    DLWARN("Save As cancelled", NAME);
                    return false;
                }

                qDebug() << NAME << ": saving as new file path"
                         << "path =" << chosen;

                m_path = chosen;
                return write(content, dialog_parent);
            }

            // reads a file from disk into a QByteArray
            // returns false and logs on failure
            static bool bread(const QString& path, QByteArray& out) {
                qDebug() << NAME << ": reading binary file"
                         << "path =" << path;

                QFile f(path);
                if (!f.open(QIODevice::ReadOnly)) {
                    qWarning() << NAME << ": failed to open file for binary read"
                               << "path =" << path
                               << "error =" << f.errorString();
                    DLERROR(QString("Cannot read '%1': %2").arg(path, f.errorString()), NAME);
                    return false;
                }

                out = f.readAll();
                qint64 bytes_read = f.pos();
                f.close();

                if (out.isEmpty()) {
                    qWarning() << NAME << ": file is empty"
                               << "path =" << path;
                    return false;
                }

                qInfo() << NAME << ": binary file read successfully"
                        << "path =" << path
                        << "size =" << bytes_read << "bytes";

                return true;
            }

        signals:
            void content_saved(const QString& path);

        protected:
            QString m_path;
    };

} // namespace lc3kit::ide
