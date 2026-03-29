#ifndef URLUTILS_H
#define URLUTILS_H

#include <QUrl>

class QString;

namespace browser {
QUrl makeUrlOrSearch(const QString &text);
}

#endif // URLUTILS_H
