#include "BrowserWindow.h"
#include "UIStyleSheet.h"
#include "UITheme.h"
#include "../storage/Settings.h"

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QTabBar>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWidget>

BrowserWindow::BrowserWindow(const QUrl &home, QWidget *parent)
    : QMainWindow(parent), m_homeUrl(home)
{
    // Use native window frame for proper layout management
    // setWindowFlag(Qt::FramelessWindowHint);

    QMenu *mainMenu = new QMenu(this);
    QAction *newTabAction = nullptr;
    QToolBar *toolbar = buildNavigationToolbar(mainMenu, newTabAction);

    buildCentralLayout(toolbar);

    QTabBar *tabBar = m_tabs->tabBar();
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    tabBar->setElideMode(Qt::ElideRight);
    tabBar->setUsesScrollButtons(true);
    tabBar->setExpanding(false);
    tabBar->setIconSize(QSize(16, 16));
    tabBar->setDrawBase(false);

    updateTabStyles();
    setupTabBarContextMenu(tabBar);
    setupSignals(newTabAction);
    setupMenuActions(mainMenu);

    createTab(m_homeUrl);
}

QToolBar* BrowserWindow::buildNavigationToolbar(QMenu *mainMenu, QAction *&newTabAction)
{
    using namespace ui::theme;

    QToolBar *toolbar = addToolBar("Navigation");
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(spacing::ICON_SIZE, spacing::ICON_SIZE));
    toolbar->setMaximumHeight(spacing::TOOLBAR_HEIGHT);

    mainMenu->setStyleSheet(ui::StyleSheet::menuStyle(darkMode));

    // Navigation buttons - lighter and more neutral
    QAction *backAction = toolbar->addAction("←");
    backAction->setToolTip("Voltar");
    m_backAction = backAction;
    
    QAction *forwardAction = toolbar->addAction("→");
    forwardAction->setToolTip("Avançar");
    m_forwardAction = forwardAction;
    
    QAction *reloadAction = toolbar->addAction("↻");
    reloadAction->setToolTip("Recarregar");
    m_reloadAction = reloadAction;

    // Add spacing before URL bar
    QWidget *spacer = new QWidget();
    spacer->setFixedWidth(spacing::PADDING_SM);
    toolbar->addWidget(spacer);

    // URL bar - clear solid surface
    QLineEdit *urlEdit = new QLineEdit();
    m_urlEdit = urlEdit;
    urlEdit->setMinimumWidth(340);
    urlEdit->setMaximumHeight(30);
    urlEdit->setPlaceholderText("Pesquisar ou digitar endereço");
    urlEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    urlEdit->setStyleSheet(ui::StyleSheet::urlbarStyle(darkMode));
    toolbar->addWidget(urlEdit);

    // Add spacing after URL bar
    QWidget *spacer2 = new QWidget();
    spacer2->setFixedWidth(spacing::PADDING_SM);
    toolbar->addWidget(spacer2);

    // New tab button
    newTabAction = toolbar->addAction("+");
    newTabAction->setToolTip("Nova aba");

    // Menu button
    QToolButton *menuButton = new QToolButton();
    menuButton->setText("⋮");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setMenu(mainMenu);
    menuButton->setToolTip("Menu");
    menuButton->setAutoRaise(true);
    toolbar->addWidget(menuButton);

    // Apply toolbar style
    toolbar->setStyleSheet(ui::StyleSheet::toolbarStyle(darkMode));

    return toolbar;
}


void BrowserWindow::buildCentralLayout(QToolBar *toolbar)
{
    m_tabs = new QTabWidget(this);
    m_tabs->setDocumentMode(true);
    m_tabs->setTabsClosable(true);
    m_tabs->setMovable(true);
    m_tabs->setStyleSheet(ui::StyleSheet::mainWindowStyle(darkMode));

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(m_tabs);
    setCentralWidget(central);
}

void BrowserWindow::setupSignals(QAction *newTabAction)
{
    QObject::connect(newTabAction, &QAction::triggered, [this]() {
        createTab(m_homeUrl);
    });

    QObject::connect(m_reloadAction, &QAction::triggered, this, &BrowserWindow::onReload);
    QObject::connect(m_backAction, &QAction::triggered, this, &BrowserWindow::onBack);
    QObject::connect(m_forwardAction, &QAction::triggered, this, &BrowserWindow::onForward);

    QObject::connect(m_tabs, &QTabWidget::tabCloseRequested, [this](int index) {
        closeTabAt(index);
    });

    QObject::connect(m_tabs, &QTabWidget::currentChanged, [this](int index) {
        if (index == -1) {
            return;
        }

        QWebEngineView *view = getViewFromIndex(index);
        if (view) {
            m_urlEdit->setText(view->url().toString());
        } else {
            m_urlEdit->clear();
        }

        updateNavigationStateForView(view);
    });

    QObject::connect(m_urlEdit, &QLineEdit::returnPressed, this, &BrowserWindow::onUrlEntered);
}
