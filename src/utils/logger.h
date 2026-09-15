#pragma once

#include <QDebug>
#include <QObject>
#include <QString>

namespace lc3kit::ide {
    enum class qlog_level {
        LOG,
        WARN,
        ERROR
    }; 

    struct qlog_event {
        qlog_level level;
        QString      message;
        QString      sender;
    };

    class Logger : public QObject {
        Q_OBJECT

        private:
            explicit Logger(QObject* parent = nullptr) : QObject(parent) {}

            // non-copyable, non-movable
            Logger(const Logger&)            = delete;
            Logger& operator=(const Logger&) = delete;

        public:
            static Logger* instance() {
                static Logger s_instance;
                return &s_instance;
            }

            void log(const qlog_event& event) {
                emit logged(event);
            }

            // convenience overloads
            void log(const QString& message, const QString& sender="IDE") {
                log({ qlog_level::LOG, message, sender });
            }
            
            void warn(const QString& message, const QString& sender="IDE") {
                log({ qlog_level::WARN, message, sender });
            }

            void error(const QString& message, const QString& sender="IDE") {
                log({ qlog_level::ERROR, message, sender });
            }

        signals:
            void logged(const qlog_event& event);
    };

    inline Logger* logger = Logger::instance();

    #define DTLOG(...)    qDebug() << __VA_ARGS__
    #define DTINFO(...)   qInfo() << __VA_ARGS__
    #define DTWARN(...)   qWarning() << __VA_ARGS__
    #define DTERROR(...)  qCritical() << __VA_ARGS__
    #define DTFATAL(...)  qFatal() << __VA_ARGS__

    #define DLINFO logger->log
    #define DLERROR logger->error
    #define DLWARN logger->warn
    #define DLLOG logger->log
    
} // namespace name
