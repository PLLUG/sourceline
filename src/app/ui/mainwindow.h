#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "contentfortab.h"

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
    QSystemTrayIcon *mTrayIcon;
    QMenu *mTrayMenu;
    CustomTabBar *mTabBar;
    TabsAPI *mTabsAPI;
    int mAmountOpenedTabs;


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
