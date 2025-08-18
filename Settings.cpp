#include "Settings.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>

bool darkMode = false;

static QString configDir() {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    if (dir.isEmpty()) dir = QDir::homePath() + "/.config";
    dir += "/simplebrowser";
    QDir d(dir);
    if (!d.exists()) d.mkpath(".");
    return dir;
}

static QString settingsFilePath() { return configDir() + "/settings.json"; }
static QString sessionFilePath()  { return configDir() + "/session.json"; }

void applyDarkMode(bool enable) {
    if (!qApp) return;
    if (enable) {
        qApp->setStyleSheet(
            "QMainWindow { background-color: #121212; color: #e0e0e0; }"
            "QWidget { background-color: #121212; color: #e0e0e0; }"
            "QToolBar { background-color: #181818; border: none; spacing: 6px; }"
            "QToolBar > * { background: transparent; }"
            "QLineEdit, QTextEdit, QPlainTextEdit { background-color: #1e1e1e; color: #e0e0e0; border: 1px solid #333; }"
            "QToolBar QLineEdit { min-width: 200px; }"
            "QTabWidget::pane { background: #121212; }"
            "QTabBar::tab { background: #1a1a1a; color: #e0e0e0; padding: 6px; margin: 1px; }"
            "QTabBar::tab:selected { background: #252525; }"
            "QMenu, QMenuBar, QDialog, QMessageBox { background: #161616; color: #e0e0e0; }"
            "QMenu::item:selected { background: #2a2a2a; }"
            "QToolButton { background: transparent; color: #e0e0e0; border: none; }"
            "QPushButton { background: #282828; color: #e0e0e0; border: 1px solid #333; padding: 4px 8px; }"
            "QCheckBox { color: #e0e0e0; }"
        );
    } else {
        qApp->setStyleSheet("");
    }
}

QUrl loadHomepageOrDefault() {
    QFile f(settingsFilePath());
    if (!f.exists()) return QUrl("https://duckduckgo.com");
    if (!f.open(QFile::ReadOnly)) return QUrl("https://duckduckgo.com");
    QByteArray data = f.readAll();
    f.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return QUrl("https://duckduckgo.com");
    QJsonObject obj = doc.object();
    darkMode = obj.value("darkMode").toBool(false);
    QString url = obj.value("homepage").toString();
    if (url.isEmpty()) return QUrl("https://duckduckgo.com");
    return QUrl::fromUserInput(url);
}

void saveSettingsHomepage(const QUrl &home) {
    QJsonObject obj;
    obj["homepage"] = home.toString();
    obj["darkMode"] = darkMode;
    QJsonDocument doc(obj);
    QFile f(settingsFilePath());
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        f.write(doc.toJson());
        f.close();
    }
}

QString sessionPath() { return sessionFilePath(); }
