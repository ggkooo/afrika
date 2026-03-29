#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QUrl>

class QTabWidget;
class QLineEdit;
class QAction;
class QWebEngineView;
class QWidget;
class QPushButton;
class QWebEngineHistory;
class QMenu;
class QToolBar;
class QTabBar;

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit BrowserWindow(const QUrl &home, QWidget *parent = nullptr);
    void saveSession();
    void restoreSession();
    void clearSession();

private:
    QUrl m_homeUrl;
    QTabWidget *m_tabs;
    QLineEdit *m_urlEdit;
    QAction *m_backAction;
    QAction *m_forwardAction;
    QAction *m_reloadAction;

    QWebEngineView* getViewFromIndex(int index) const;
    QWebEngineView* getCurrentView() const;
    void createTab(const QUrl &initialUrl);
    void ensureViewForIndex(int index);
    void applyCustomCloseButton(QWidget *tabContainer);
    void updateAllTabCloseButtons();
    void updateTabStyles();
    void closeTabAt(int index);
    void setupMenuActions(QMenu *mainMenu);
    void setupTabBarContextMenu(QTabBar *tabBar);
    void setupSignals(QAction *newTabAction);
    void updateNavigationStateForView(QWebEngineView *view);
    void showSettingsDialog();
    QToolBar* buildNavigationToolbar(QMenu *mainMenu, QAction *&newTabAction);
    void buildCentralLayout(QToolBar *toolbar);

    // Retorna o histórico da aba atual, ou nullptr se não houver.
    QWebEngineHistory* getCurrentHistory() const;

    void ensureTabLimit();
    static constexpr int MAX_TABS = 16;

private slots:
    void onUrlEntered();
    void onBack();
    void onForward();
    void onReload();
    void clearCache();
};

#endif // BROWSERWINDOW_H
