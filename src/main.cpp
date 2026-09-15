#include "themes/qrc.h"

#include <QDebug>
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QDir>
#include <QSettings>
#include <QIcon>

#include "core/main_window.h"

void setup_app_identity(QApplication& app) {
    app.setApplicationName(lc3kit::ide::appmanifest.name());
    app.setApplicationDisplayName(lc3kit::ide::appmanifest.pretty_name());
    app.setApplicationVersion(lc3kit::ide::appmanifest.version());
    app.setOrganizationDomain(lc3kit::ide::appmanifest.domain());
    app.setOrganizationName(lc3kit::ide::appmanifest.organization());

    app.setWindowIcon(QIcon(":/img/lc3kit-ide"));
}

void setup_app_style(QApplication& app) {
    app.setStyle(new lc3kit::ide::ProxyStyle(app.style(), 1));
    qDebug() << "Applied proxy style with UI scale factor = 1.0";
}

void setup_app_fonts(QApplication& app) {
    // Ubuntu for UI
    bool fonts_ok = true;
    if (QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Regular") < 0) {
        qWarning() << "Failed to load embedded font: Ubuntu-Regular - UI font may not render correctly";
        fonts_ok = false;
    }
    if (QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Medium") < 0) {
        qWarning() << "Failed to load embedded font: Ubuntu-Medium - UI font rendering degraded";
        fonts_ok = false;
    }
    if (QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Bold") < 0) {
        qWarning() << "Failed to load embedded font: Ubuntu-Bold - UI font rendering degraded";
        fonts_ok = false;
    }
    // Fira Code for editor
    if (QFontDatabase::addApplicationFont(":/fonts/FiraCode-Regular") < 0) {
        qWarning() << "Failed to load embedded font: FiraCode-Regular - editor font may not render correctly";
        fonts_ok = false;
    }
    if (QFontDatabase::addApplicationFont(":/fonts/FiraCode-Medium") < 0) {
        qWarning() << "Failed to load embedded font: FiraCode-Medium - editor font rendering degraded";
        fonts_ok = false;
    }
    if (fonts_ok) {
        qDebug() << "All application fonts loaded successfully";
    }

    QFont ui_font("Ubuntu", 10);
    ui_font.setStyleHint(QFont::SansSerif);
    app.setFont(ui_font);
    qDebug() << "Set application font: Ubuntu, point size = 10";
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    setup_app_identity(app);

    qInfo() << "Application started:"
            << "name =" << app.applicationDisplayName()
            << "version =" << app.applicationVersion()
            << "Qt version =" << qVersion()
            << "lc3kit version =" << __LC3_KIT_LIB_VERSION;

    setup_app_identity(app);
    
    setup_app_style(app);
    
    setup_app_fonts(app);
    
    // splash
    qDebug() << "Loading splash screen from resource: :/img/splashscreen";
    QPixmap splash_pix(":/img/splashscreen");
    QSplashScreen splash(splash_pix, Qt::WindowStaysOnTopHint);

    if (!splash_pix.isNull()) {
        splash.show();
        splash.showMessage("Loading...", Qt::AlignBottom | Qt::AlignHCenter, QColor("#88C0D0"));
        app.processEvents();
        qDebug() << "Splash screen displayed successfully";
    } 
    else {
        qWarning() << "Splash screen resource not found at :/img/splashscreen - skipping splash display";
    }

    // main window
    qDebug() << "Constructing main window";
    lc3kit::ide::MainWindow window;

    QObject::connect(&window, &lc3kit::ide::MainWindow::ready, [&](lc3kit::ide::MainWindow*) {
        splash.finish(&window);
        window.show();
        qInfo() << "Main window displayed";
    });

    window.init();

    return app.exec();
}
