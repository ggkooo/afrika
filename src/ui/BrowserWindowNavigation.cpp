#include "BrowserWindow.h"
#include "../utils/UrlUtils.h"

#include <QLineEdit>
#include <QWebEngineHistory>
#include <QWebEngineView>

void BrowserWindow::onUrlEntered()
{
    QWebEngineView *v = getCurrentView();
    if (!v) {
        return;
    }

    QUrl dest = browser::makeUrlOrSearch(m_urlEdit->text());
    if (dest.isValid() && !dest.isEmpty()) {
        v->load(dest);
    }
}

void BrowserWindow::onBack()
{
    QWebEngineHistory *h = getCurrentHistory();
    if (h && h->canGoBack()) {
        h->back();
    }
}

void BrowserWindow::onForward()
{
    QWebEngineHistory *h = getCurrentHistory();
    if (h && h->canGoForward()) {
        h->forward();
    }
}

void BrowserWindow::onReload()
{
    QWebEngineView *v = getCurrentView();
    if (v) {
        v->reload();
    }
}
