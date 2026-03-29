#include "UrlUtils.h"

#include <QRegularExpression>
#include <QString>

namespace browser {
QUrl makeUrlOrSearch(const QString &text)
{
    const QString t = text.trimmed();
    if (t.isEmpty()) {
        return QUrl();
    }

    static const QRegularExpression schemeRe("^[a-zA-Z][a-zA-Z0-9+.-]*:");
    if (schemeRe.match(t).hasMatch()) {
        return QUrl::fromUserInput(t);
    }

    if (t.contains(' ') || !t.contains('.')) {
        const QByteArray enc = QUrl::toPercentEncoding(t);
        return QUrl(QString("https://duckduckgo.com/?q=") + QString(enc));
    }

    return QUrl::fromUserInput(t);
}
} // namespace browser
