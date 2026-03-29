#include <QApplication>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

#include "ui/BrowserWindow.h"
#include "storage/Settings.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setApplicationName("Afrika");

    // Enable high-DPI pixmaps for crisper UI on HiDPI displays
#if QT_VERSION < QT_VERSION_CHECK(6,6,0)
    // Attribute deprecated in Qt 6.6+ where high-DPI pixmaps are always enabled
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#else
    // Qt >= 6.6 enables high-DPI pixmaps by default — no action needed
#endif

    // Configure a shared WebEngine profile for all views to improve caching and reduce memory
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    if (cacheDir.isEmpty()) cacheDir = QDir::homePath() + "/.cache";
    cacheDir += "/afrika";
    QDir d(cacheDir);
    if (!d.exists()) d.mkpath(".");

    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setCachePath(cacheDir + "/httpcache");
    profile->setPersistentStoragePath(cacheDir + "/storage");
    profile->setHttpCacheMaximumSize(50 * 1024 * 1024); // 50 MB cache
    profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

    // Global WebEngine settings via the shared profile (Qt6): disable plugins to save resources, keep local storage
    QWebEngineSettings *gs = profile->settings();
    gs->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    gs->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    gs->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, true);

    QUrl homeUrl = loadHomepageOrDefault();
    applyDarkMode(darkMode);

    BrowserWindow w(homeUrl);
    w.resize(1920, 1080);
    w.show();

    return app.exec();
}
