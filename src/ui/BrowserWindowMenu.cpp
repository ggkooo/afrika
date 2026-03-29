#include "BrowserWindow.h"
#include "UIStyleSheet.h"
#include "../storage/Settings.h"

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QTabBar>
#include <QTabWidget>
#include <QWebEngineView>

void BrowserWindow::setupTabBarContextMenu(QTabBar *tabBar)
{
    QObject::connect(tabBar, &QTabBar::customContextMenuRequested, [this](const QPoint &pos) {
        int index = m_tabs->tabBar()->tabAt(pos);
        if (index == -1) {
            return;
        }

        QMenu menu;
        QAction *close = menu.addAction("Fechar");
        QAction *duplicate = menu.addAction("Duplicar");
        QAction *openNew = menu.addAction("Abrir em nova aba");

        QAction *selected = menu.exec(m_tabs->tabBar()->mapToGlobal(pos));
        if (!selected) {
            return;
        }

        if (selected == close) {
            closeTabAt(index);
            return;
        }

        if (selected == duplicate || selected == openNew) {
            QWebEngineView *v = getViewFromIndex(index);
            if (v) {
                createTab(v->url());
            }
        }
    });
}

void BrowserWindow::setupMenuActions(QMenu *mainMenu)
{
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
        QMessageBox::information(this, "Sobre", "Afrika - protótipo com Qt WebEngine\n(feito para estudo)");
    });
    QObject::connect(settingsAct, &QAction::triggered, [this]() {
        showSettingsDialog();
    });
}

void BrowserWindow::showSettingsDialog()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Configurações");
    dlg.setMinimumWidth(400);
    dlg.setStyleSheet(ui::StyleSheet::dialogStyle(darkMode));

    QFormLayout *form = new QFormLayout(&dlg);
    form->setSpacing(16);
    form->setContentsMargins(24, 24, 24, 24);

    QLabel *homeLabel = new QLabel("Página inicial:");
    homeLabel->setStyleSheet(QString("color: %1;").arg(darkMode ? "#ffffff" : "#1a1a1a"));
    QLineEdit *homeEdit = new QLineEdit(m_homeUrl.toString(), &dlg);
    homeEdit->setStyleSheet(ui::StyleSheet::urlbarStyle(darkMode));
    form->addRow(homeLabel, homeEdit);

    QCheckBox *darkCheck = new QCheckBox("Ativar modo escuro", &dlg);
    darkCheck->setChecked(darkMode);
    darkCheck->setStyleSheet(QString("color: %1;").arg(darkMode ? "#ffffff" : "#1a1a1a"));
    form->addRow(darkCheck);

    QDialogButtonBox *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    bb->setStyleSheet(ui::StyleSheet::buttonStyle(darkMode));
    form->addRow(bb);

    QObject::connect(bb, &QDialogButtonBox::accepted, [this, homeEdit, &dlg, darkCheck]() {
        QUrl newHome = QUrl::fromUserInput(homeEdit->text());
        if (newHome.isValid()) {
            m_homeUrl = newHome;
            darkMode = darkCheck->isChecked();
            applyDarkMode(darkMode);
            updateTabStyles();
            updateAllTabCloseButtons();
            dlg.setStyleSheet(ui::StyleSheet::dialogStyle(darkMode));
            saveSettingsHomepage(m_homeUrl);
        }
        dlg.accept();
    });

    QObject::connect(bb, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    dlg.exec();
}
