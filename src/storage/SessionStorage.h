#ifndef SESSIONSTORAGE_H
#define SESSIONSTORAGE_H

#include <QStringList>

struct SessionData {
    QStringList tabs;
    int activeIndex = 0;
};

bool saveSessionData(const QString &path, const SessionData &data);
bool loadSessionData(const QString &path, SessionData &data);
bool clearSessionData(const QString &path);

#endif // SESSIONSTORAGE_H
