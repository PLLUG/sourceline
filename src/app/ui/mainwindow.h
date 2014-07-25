#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include "appsettingsdialog.h"
#include "viewsettingpage.h"
#include "settings_dialog/settingstorage.h"
#include "viewsettings.h"
#include "customtabbar.h"
#include "pagemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *TrayIcon;
    QMenu *trayMenu;
    AppSettingsDialog *mSettingsDialog;
    ViewSettings *mViewSettings;
    CustomTabBar *mTabBar;
    PageManager *mPageManager;
signals:
    void mysignal();
private:
    void readSettings();
    void writeSettings();
    void applySettings();
    void resizeEvent(QResizeEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void CloseWindow();

    void on_actionClose_triggered();

    void showSettings();
    void slotPreferencesAccepted();
    //void slotPreferencesAccepted();

    void on_actionAdd_Page_triggered();
};

#endif // MAINWINDOW_H
