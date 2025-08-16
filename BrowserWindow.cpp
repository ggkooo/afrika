#include "BrowserWindow.h"
#include "Settings.h"

#include <QApplication>
#include <QToolBar>
#include <QLineEdit>
#include <QToolButton>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEngineHistory>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QLabel>
#include <QWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>

BrowserWindow::BrowserWindow(const QUrl &home, QWidget *parent)
    : QMainWindow(parent), m_homeUrl(home)
{
    // Menu and toolbar
    QMenu *mainMenu = new QMenu(this);
    QToolButton *menuButton = new QToolButton(this);
    menuButton->setText("⋮");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setToolTip("Menu");

    QToolBar *toolbar = addToolBar("Navigation");
    m_backAction = toolbar->addAction("←");
    m_forwardAction = toolbar->addAction("→");
    m_reloadAction = toolbar->addAction("⟳");
    toolbar->addSeparator();
    QAction *newTabAction = toolbar->addAction("+");

    QLineEdit *urlEdit = new QLineEdit(toolbar);
    m_urlEdit = urlEdit;
    urlEdit->setMinimumWidth(400);
    urlEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(urlEdit);
    urlEdit->setStyleSheet("border: 1px solid rgba(37, 37, 37,0.25); border-radius:12px; padding:4px;");
    QWidget *gap = new QWidget(this);
    gap->setFixedWidth(8);
    toolbar->addWidget(gap);
    menuButton->setMenu(mainMenu);
    menuButton->setAutoRaise(true);
    menuButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    toolbar->addWidget(menuButton);

    m_tabs = new QTabWidget(this);
    m_tabs->setDocumentMode(true);
    m_tabs->setTabsClosable(true);
    m_tabs->setMovable(true);
    setCentralWidget(m_tabs);

    QTabBar *tabBar = m_tabs->tabBar();
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);

    // Internal helper lambdas use members
    auto getViewFromIndexLambda = [&](int index) -> QWebEngineView * {
        if (index < 0 || index >= m_tabs->count())
            return nullptr;
        QWidget *w = m_tabs->widget(index);
        if (!w)
            return nullptr;
        return w->findChild<QWebEngineView *>();
    };

    auto getCurrentViewLambda = [&]() -> QWebEngineView * { return getViewFromIndexLambda(m_tabs->currentIndex()); };

    // createTab implementation
    auto createTabLambda = [&](const QUrl &initialUrl) -> QWebEngineView * {
        QWebEngineView *view = new QWebEngineView;
        view->load(initialUrl);

        QWidget *container = new QWidget;
        QVBoxLayout *lay = new QVBoxLayout(container);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->addWidget(view);

        int index = m_tabs->addTab(container, "Nova Aba");
        m_tabs->setCurrentIndex(index);

        QObject::connect(view, &QWebEngineView::titleChanged, [this, container](const QString &title) {
            int i = m_tabs->indexOf(container);
            if (i != -1)
                m_tabs->setTabText(i, title);
        });

        QObject::connect(view, &QWebEngineView::urlChanged, [this, container](const QUrl &url) {
            int i = m_tabs->indexOf(container);
            if (i == m_tabs->currentIndex())
                m_urlEdit->setText(url.toString());
        });

        auto updateNav = [this, container]() {
            int i = m_tabs->indexOf(container);
            if (i == -1)
                return;
            QWidget *w = m_tabs->widget(i);
            QWebEngineView *v = w->findChild<QWebEngineView *>();
            if (!v)
                return;
            m_backAction->setEnabled(v->history()->canGoBack());
            m_forwardAction->setEnabled(v->history()->canGoForward());
            m_reloadAction->setEnabled(true);
        };

        QObject::connect(view, &QWebEngineView::loadFinished, [updateNav](bool) { updateNav(); });
        QObject::connect(view, &QWebEngineView::loadStarted, [updateNav]() { updateNav(); });
        QObject::connect(view, &QWebEngineView::urlChanged, [updateNav](const QUrl &) { updateNav(); });

        return view;
    };

    // expose methods using lambdas
    auto makeUrlOrSearch = [&](const QString &text) -> QUrl {
        QString t = text.trimmed();
        if (t.isEmpty())
            return QUrl();
        QRegularExpression schemeRe("^[a-zA-Z][a-zA-Z0-9+.-]*:");
        if (schemeRe.match(t).hasMatch()) {
            return QUrl::fromUserInput(t);
        }
        if (t.contains(' ')) {
            QByteArray enc = QUrl::toPercentEncoding(t);
            return QUrl(QString("https://duckduckgo.com/?q=") + QString(enc));
        }
        if (t.contains('.')) {
            return QUrl::fromUserInput(t);
        }
        QByteArray enc = QUrl::toPercentEncoding(t);
        return QUrl(QString("https://duckduckgo.com/?q=") + QString(enc));
    };

    // Hook up actions
    QObject::connect(newTabAction, &QAction::triggered, [this, createTabLambda]() { createTabLambda(m_homeUrl); });

    // Hook up navigation actions to member slots (avoid lambdas that capture local lambdas)
    QObject::connect(m_reloadAction, &QAction::triggered, this, &BrowserWindow::onReload);
    QObject::connect(m_backAction, &QAction::triggered, this, &BrowserWindow::onBack);
    QObject::connect(m_forwardAction, &QAction::triggered, this, &BrowserWindow::onForward);

    QObject::connect(m_tabs, &QTabWidget::tabCloseRequested, [this](int index) {
        QWidget *w = m_tabs->widget(index);
        m_tabs->removeTab(index);
        delete w;
        // If no tabs left, open a new one instead of quitting the app
        if (m_tabs->count() == 0) {
            createTab(m_homeUrl);
        }
    });

    QObject::connect(m_tabs, &QTabWidget::currentChanged, [this, getViewFromIndexLambda](int index) {
        if (index == -1)
            return;
        QWebEngineView *view = getViewFromIndexLambda(index);
        if (view)
            m_urlEdit->setText(view->url().toString());
        else
            m_urlEdit->clear();

        if (view) {
            m_backAction->setEnabled(view->history()->canGoBack());
            m_forwardAction->setEnabled(view->history()->canGoForward());
            m_reloadAction->setEnabled(true);
        } else {
            m_backAction->setEnabled(false);
            m_forwardAction->setEnabled(false);
            m_reloadAction->setEnabled(false);
        }
    });

    QObject::connect(urlEdit, &QLineEdit::returnPressed, this, &BrowserWindow::onUrlEntered);

    // Tab bar context menu
    QObject::connect(tabBar, &QTabBar::customContextMenuRequested,
                     [this, createTabLambda, getViewFromIndexLambda](const QPoint &pos) {
                         int index = m_tabs->tabBar()->tabAt(pos);
                         if (index == -1)
                             return;
                         QMenu menu;
                         QAction *close = menu.addAction("Fechar");
                         QAction *duplicate = menu.addAction("Duplicar");
                         QAction *openNew = menu.addAction("Abrir em nova aba");
                         QAction *selected = menu.exec(m_tabs->tabBar()->mapToGlobal(pos));
                         if (!selected)
                             return;
                         if (selected == close) {
                             QWidget *w = m_tabs->widget(index);
                             m_tabs->removeTab(index);
                             delete w;
                             if (m_tabs->count() == 0) {
                                 createTab(m_homeUrl);
                             }
                         } else if (selected == duplicate) {
                             QWebEngineView *v = getViewFromIndexLambda(index);
                             if (v)
                                 createTabLambda(v->url());
                         } else if (selected == openNew) {
                             QWebEngineView *v = getViewFromIndexLambda(index);
                             if (v)
                                 createTabLambda(v->url());
                         }
                     });

    // Populate main menu with session/settings/about/quit
    QAction *saveAct = mainMenu->addAction("Salvar sessão");
    QAction *restoreAct = mainMenu->addAction("Restaurar sessão");
    QAction *clearAct = mainMenu->addAction("Limpar sessão");
    QAction *clearCacheAct = mainMenu->addAction("Limpar cache");

    QObject::connect(saveAct, &QAction::triggered, this, &BrowserWindow::saveSession);
    QObject::connect(restoreAct, &QAction::triggered, this, &BrowserWindow::restoreSession);
    QObject::connect(clearAct, &QAction::triggered, this, &BrowserWindow::clearSession);
    QObject::connect(clearCacheAct, &QAction::triggered, this, &BrowserWindow::clearCache);

    QAction *settingsAct = mainMenu->addAction("Configurações");
    mainMenu->addSeparator();
    QAction *aboutAct = mainMenu->addAction("Sobre");
    QAction *quitAct = mainMenu->addAction("Sair");

    QObject::connect(quitAct, &QAction::triggered, qApp, &QApplication::quit);
    QObject::connect(aboutAct, &QAction::triggered, [this]() {
        QMessageBox::information(this, "Sobre", "SimpleBrowser - protótipo com Qt WebEngine\n(feito para estudo)");
    });

    QObject::connect(settingsAct, &QAction::triggered, [this]() {
        QDialog dlg(this);
        dlg.setWindowTitle("Configurações");
        QFormLayout *form = new QFormLayout(&dlg);
        QLineEdit *homeEdit = new QLineEdit(m_homeUrl.toString(), &dlg);
        form->addRow(new QLabel("Página inicial:"), homeEdit);
        QCheckBox *darkCheck = new QCheckBox("Ativar modo escuro", &dlg);
        darkCheck->setChecked(darkMode);
        form->addRow(darkCheck);
        QDialogButtonBox *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        form->addWidget(bb);
        QObject::connect(bb, &QDialogButtonBox::accepted, [this, homeEdit, &dlg, darkCheck]() {
            QUrl newHome = QUrl::fromUserInput(homeEdit->text());
            if (newHome.isValid()) {
                m_homeUrl = newHome;
                darkMode = darkCheck->isChecked();
                applyDarkMode(darkMode);
                saveSettingsHomepage(m_homeUrl);
            }
            dlg.accept();
        });
        QObject::connect(bb, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
        dlg.exec();
    });

    // initial tab
    createTabLambda(m_homeUrl);
}

QWebEngineView *BrowserWindow::getViewFromIndex(int index) const
{
    if (index < 0 || index >= m_tabs->count())
        return nullptr;
    QWidget *w = m_tabs->widget(index);
    if (!w)
        return nullptr;
    return w->findChild<QWebEngineView *>();
}

QWebEngineView *BrowserWindow::getCurrentView() const
{
    return getViewFromIndex(m_tabs->currentIndex());
}

void BrowserWindow::createTab(const QUrl &initialUrl)
{
    // Delegate to the previous lambda behavior by duplicating code for simplicity
    QWebEngineView *view = new QWebEngineView;
    view->load(initialUrl);

    QWidget *container = new QWidget;
    QVBoxLayout *lay = new QVBoxLayout(container);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(view);

    int index = m_tabs->addTab(container, "Nova Aba");
    m_tabs->setCurrentIndex(index);

    QObject::connect(view, &QWebEngineView::titleChanged, [this, container](const QString &title) {
        int i = m_tabs->indexOf(container);
        if (i != -1)
            m_tabs->setTabText(i, title);
    });

    QObject::connect(view, &QWebEngineView::urlChanged, [this, container](const QUrl &url) {
        int i = m_tabs->indexOf(container);
        if (i == m_tabs->currentIndex())
            m_urlEdit->setText(url.toString());
    });

    auto updateNav = [this, container]() {
        int i = m_tabs->indexOf(container);
        if (i == -1)
            return;
        QWidget *w = m_tabs->widget(i);
        QWebEngineView *v = w->findChild<QWebEngineView *>();
        if (!v)
            return;
        m_backAction->setEnabled(v->history()->canGoBack());
        m_forwardAction->setEnabled(v->history()->canGoForward());
        m_reloadAction->setEnabled(true);
    };

    QObject::connect(view, &QWebEngineView::loadFinished, [updateNav](bool) { updateNav(); });
    QObject::connect(view, &QWebEngineView::loadStarted, [updateNav]() { updateNav(); });
    QObject::connect(view, &QWebEngineView::urlChanged, [updateNav](const QUrl &) { updateNav(); });
}

void BrowserWindow::ensureViewForIndex(int index)
{
    // For now views are created eagerly in createTab, so this is a noop.
    Q_UNUSED(index);
}

void BrowserWindow::saveSession()
{
    QJsonObject root;
    QJsonArray arr;
    for (int i = 0; i < m_tabs->count(); ++i) {
        QWebEngineView *v = getViewFromIndex(i);
        if (v)
            arr.append(v->url().toString());
    }
    root["tabs"] = arr;
    root["active"] = m_tabs->currentIndex();
    QJsonDocument doc(root);
    QFile f(sessionPath());
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        f.write(doc.toJson());
        f.close();
    }
    QMessageBox::information(this, "Sessão", "Sessão salva com sucesso.");
}

void BrowserWindow::restoreSession()
{
    QFile f(sessionPath());
    if (!f.exists()) {
        QMessageBox::warning(this, "Sessão", "Nenhuma sessão salva encontrada.");
        return;
    }
    if (!f.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "Sessão", "Falha ao abrir arquivo de sessão.");
        return;
    }
    QByteArray data = f.readAll();
    f.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        return;
    QJsonObject root = doc.object();
    QJsonArray arr = root.value("tabs").toArray();
    int active = root.value("active").toInt(0);
    while (m_tabs->count() > 0) {
        QWidget *w = m_tabs->widget(0);
        m_tabs->removeTab(0);
        delete w;
    }
    for (const QJsonValue &val : arr) {
        QString s = val.toString();
        createTab(QUrl::fromUserInput(s));
    }
    if (m_tabs->count() > 0)
        m_tabs->setCurrentIndex(qBound(0, active, m_tabs->count() - 1));
}

void BrowserWindow::clearSession()
{
    QFile f(sessionPath());
    if (f.exists())
        f.remove();
    QMessageBox::information(this, "Sessão", "Sessão limpa.");
}

void BrowserWindow::ensureTabLimit()
{
    while (m_tabs->count() > MAX_TABS) {
        QWidget *w = m_tabs->widget(0);
        m_tabs->removeTab(0);
        delete w;
    }
}

void BrowserWindow::clearCache()
{
    QWebEngineProfile *p = QWebEngineProfile::defaultProfile();
    if (p) {
        p->clearHttpCache();
        QWebEngineCookieStore *cs = p->cookieStore();
        if (cs) cs->deleteAllCookies();
    }
    QMessageBox::information(this, "Cache", "Cache e cookies limpos.");
}

// New slot implementation to handle URL/search input from the main URL bar
void BrowserWindow::onUrlEntered()
{
    QWebEngineView *v = getCurrentView();
    if (!v)
        return;
    QString txt = m_urlEdit->text();
    QString t = txt.trimmed();
    if (t.isEmpty())
        return;

    QRegularExpression schemeRe("^[a-zA-Z][a-zA-Z0-9+.-]*:");
    if (schemeRe.match(t).hasMatch()) {
        QUrl dest = QUrl::fromUserInput(t);
        if (dest.isValid())
            v->load(dest);
        return;
    }
    if (t.contains(' ')) {
        QByteArray enc = QUrl::toPercentEncoding(t);
        QUrl dest(QString("https://duckduckgo.com/?q=") + QString(enc));
        v->load(dest);
        return;
    }
    if (t.contains('.')) {
        QUrl dest = QUrl::fromUserInput(t);
        if (dest.isValid())
            v->load(dest);
        return;
    }
    QByteArray enc = QUrl::toPercentEncoding(t);
    QUrl dest(QString("https://duckduckgo.com/?q=") + QString(enc));
    v->load(dest);
}

void BrowserWindow::onBack()
{
    QWebEngineView *v = getCurrentView();
    if (!v)
        return;
    QWebEngineHistory *h = v->history();
    if (!h)
        return;
    if (h->canGoBack())
        v->back();
}

void BrowserWindow::onForward()
{
    QWebEngineView *v = getCurrentView();
    if (!v)
        return;
    QWebEngineHistory *h = v->history();
    if (!h)
        return;
    if (h->canGoForward())
        v->forward();
}

void BrowserWindow::onReload()
{
    QWebEngineView *v = getCurrentView();
    if (!v)
        return;
    v->reload();
}
