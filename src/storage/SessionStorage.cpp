#include "SessionStorage.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

bool saveSessionData(const QString &path, const SessionData &data)
{
    QJsonObject root;
    QJsonArray tabs;

    for (const QString &url : data.tabs) {
        tabs.append(url);
    }

    root["tabs"] = tabs;
    root["active"] = data.activeIndex;

    QFile f(path);
    if (!f.open(QFile::WriteOnly | QFile::Truncate)) {
        return false;
    }

    f.write(QJsonDocument(root).toJson());
    f.close();
    return true;
}

bool loadSessionData(const QString &path, SessionData &data)
{
    QFile f(path);
    if (!f.exists() || !f.open(QFile::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();

    if (!doc.isObject()) {
        return false;
    }

    QJsonObject root = doc.object();
    QJsonArray tabs = root.value("tabs").toArray();

    data.tabs.clear();
    for (const QJsonValue &value : tabs) {
        data.tabs.append(value.toString());
    }

    data.activeIndex = root.value("active").toInt(0);
    return true;
}

bool clearSessionData(const QString &path)
{
    QFile f(path);
    return !f.exists() || f.remove();
}
