#include "BrowserWindow.h"
#include "../storage/Settings.h"
#include "UIStyleSheet.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWebEngineHistory>
#include <QWebEngineView>
#include <QWidget>

QWebEngineView *BrowserWindow::getViewFromIndex(int index) const
{
    if (index < 0 || index >= m_tabs->count()) {
        return nullptr;
    }

    QWidget *w = m_tabs->widget(index);
    if (!w) {
        return nullptr;
    }

    return w->findChild<QWebEngineView *>();
}

QWebEngineView *BrowserWindow::getCurrentView() const
{
    return getViewFromIndex(m_tabs->currentIndex());
}

QWebEngineHistory* BrowserWindow::getCurrentHistory() const
{
    QWebEngineView *v = getCurrentView();
    return v ? v->history() : nullptr;
}

void BrowserWindow::updateNavigationStateForView(QWebEngineView *view)
{
    if (view) {
        m_backAction->setEnabled(view->history()->canGoBack());
        m_forwardAction->setEnabled(view->history()->canGoForward());
        m_reloadAction->setEnabled(true);
    } else {
        m_backAction->setEnabled(false);
        m_forwardAction->setEnabled(false);
        m_reloadAction->setEnabled(false);
    }
}

void BrowserWindow::applyCustomCloseButton(QWidget *tabContainer)
{
    if (!tabContainer) {
        return;
    }

    int idx = m_tabs->indexOf(tabContainer);
    if (idx < 0) {
        return;
    }

    QTabBar *bar = m_tabs->tabBar();
    if (!bar) {
        return;
    }

    QWidget *oldBtn = bar->tabButton(idx, QTabBar::RightSide);
    if (oldBtn) {
        oldBtn->deleteLater();
    }

    QPushButton *btn = new QPushButton("×");
    btn->setFlat(true);
    btn->setCursor(Qt::ArrowCursor);
    btn->setFixedSize(28, 28);
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setToolTip("Fechar aba");
    btn->setStyleSheet(ui::StyleSheet::tabCloseButtonStyle(darkMode));

    bar->setTabButton(idx, QTabBar::RightSide, btn);
    QObject::connect(btn, &QPushButton::clicked, this, [this, tabContainer]() {
        int i = m_tabs->indexOf(tabContainer);
        if (i != -1) {
            closeTabAt(i);
        }
    });
}

void BrowserWindow::updateAllTabCloseButtons()
{
    for (int i = 0; i < m_tabs->count(); ++i) {
        QWidget *w = m_tabs->widget(i);
        applyCustomCloseButton(w);
    }
}

void BrowserWindow::updateTabStyles()
{
    if (!m_tabs) {
        return;
    }

    QTabBar *bar = m_tabs->tabBar();
    if (!bar) {
        return;
    }

    bar->setStyleSheet(ui::StyleSheet::tabbarStyle(darkMode));
}

void BrowserWindow::createTab(const QUrl &initialUrl)
{
    QWebEngineView *view = new QWebEngineView;
    view->load(initialUrl);

    QWidget *container = new QWidget;
    QVBoxLayout *lay = new QVBoxLayout(container);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    lay->addWidget(view);

    int index = m_tabs->addTab(container, "Nova Aba");
    m_tabs->setCurrentIndex(index);
    applyCustomCloseButton(container);
    updateTabStyles();

    // Atualizar título e favicon conforme a página carrega
    QObject::connect(view, &QWebEngineView::titleChanged, [this, container](const QString &title) {
        int i = m_tabs->indexOf(container);
        if (i != -1) {
            // Truncate título longo com ellipsis
            QString displayTitle = title;
            if (displayTitle.isEmpty()) {
                displayTitle = "Nova Aba";
            } else if (displayTitle.length() > 50) {
                displayTitle = displayTitle.left(47) + "...";
            }
            m_tabs->setTabText(i, displayTitle);
        }
    });

    // Capturar favicon
    QObject::connect(view, &QWebEngineView::iconChanged, [this, container](const QIcon &icon) {
        int i = m_tabs->indexOf(container);
        if (i != -1) {
            if (!icon.isNull()) {
                m_tabs->setTabIcon(i, icon);
            } else {
                // Usar ícone padrão se não houver favicon
                m_tabs->setTabIcon(i, QIcon());
            }
        }
    });

    QObject::connect(view, &QWebEngineView::urlChanged, [this, container](const QUrl &url) {
        int i = m_tabs->indexOf(container);
        if (i == m_tabs->currentIndex()) {
            m_urlEdit->setText(url.toString());
        }
    });

    auto updateNav = [this, container]() {
        int i = m_tabs->indexOf(container);
        if (i == -1) {
            return;
        }

        QWidget *w = m_tabs->widget(i);
        QWebEngineView *v = w ? w->findChild<QWebEngineView *>() : nullptr;
        updateNavigationStateForView(v);
    };

    QObject::connect(view, &QWebEngineView::loadFinished, [updateNav](bool) { updateNav(); });
    QObject::connect(view, &QWebEngineView::loadStarted, [updateNav]() { updateNav(); });
    QObject::connect(view, &QWebEngineView::urlChanged, [updateNav](const QUrl &) { updateNav(); });

    ensureTabLimit();
}

void BrowserWindow::ensureViewForIndex(int index)
{
    Q_UNUSED(index);
}

void BrowserWindow::ensureTabLimit()
{
    while (m_tabs->count() > MAX_TABS) {
        closeTabAt(0);
    }
}

void BrowserWindow::closeTabAt(int index)
{
    QWidget *w = m_tabs->widget(index);
    m_tabs->removeTab(index);
    delete w;

    if (m_tabs->count() == 0) {
        createTab(m_homeUrl);
    }
}
