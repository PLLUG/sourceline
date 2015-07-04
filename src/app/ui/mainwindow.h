#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// TASK: refactor: too many includes
#include <QMainWindow>
#include <QSystemTrayIcon>
//#include <QIcon>
//#include <QMenu>
//#include <QCloseEvent>
//#include <QApplication>
//#include "settings.h"
//#include "appsettingsdialog.h"
//#include "viewsettingpage.h"

class PageManager;
class CustomTabBar;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QSystemTrayIcon *TrayIcon;
    QMenu *trayMenu;
    CustomTabBar *mTabBar;
    PageManager *mPageManager;

signals:
    void mysignal();

private:
    void resizeEvent(QResizeEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

    void CloseWindow();

    void slotQuit();

    void slotAddPage();
};

#endif // MAINWINDOW_H
