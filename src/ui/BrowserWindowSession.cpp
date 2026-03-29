#include "BrowserWindow.h"
#include "../storage/SessionStorage.h"
#include "../storage/Settings.h"

#include <QMessageBox>
#include <QTabWidget>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>

void BrowserWindow::saveSession()
{
    SessionData data;

    for (int i = 0; i < m_tabs->count(); ++i) {
        QWebEngineView *v = getViewFromIndex(i);
        if (v) {
            data.tabs.append(v->url().toString());
        }
    }

    data.activeIndex = m_tabs->currentIndex();
    saveSessionData(sessionPath(), data);

    QMessageBox::information(this, "Sessão", "Sessão salva com sucesso.");
}

void BrowserWindow::restoreSession()
{
    SessionData data;
    if (!loadSessionData(sessionPath(), data)) {
        QMessageBox::warning(this, "Sessão", "Nenhuma sessão salva encontrada ou arquivo inválido.");
        return;
    }

    while (m_tabs->count() > 0) {
        closeTabAt(0);
    }

    for (const QString &tabUrl : data.tabs) {
        createTab(QUrl::fromUserInput(tabUrl));
    }

    if (m_tabs->count() > 0) {
        m_tabs->setCurrentIndex(qBound(0, data.activeIndex, m_tabs->count() - 1));
    }
}

void BrowserWindow::clearSession()
{
    clearSessionData(sessionPath());

    QMessageBox::information(this, "Sessão", "Sessão limpa.");
}

void BrowserWindow::clearCache()
{
    QWebEngineProfile *p = QWebEngineProfile::defaultProfile();
    if (p) {
        p->clearHttpCache();
        QWebEngineCookieStore *cs = p->cookieStore();
        if (cs) {
            cs->deleteAllCookies();
        }
    }

    QMessageBox::information(this, "Cache", "Cache e cookies limpos.");
}
