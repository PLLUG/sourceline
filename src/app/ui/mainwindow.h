#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "contentfortabworkplace.h"

class TabsAPI;
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
    TabsAPI *mTabsAPI;

signals:
    void mysignal();

private:
    void resizeEvent(QResizeEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

    void CloseWindow();

    void slotQuit();

    void slotAddNewWorkplace();
};

#endif // MAINWINDOW_H
