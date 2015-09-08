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

    Ui::MainWindow *getUi() const;

private:
    void resizeEvent(QResizeEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

    void slotCloseWindow();

    void slotQuit();

    void slotAddNewWorkplace();

private:
    QSystemTrayIcon *mTrayIcon;
    QMenu *mTrayMenu;
    CustomTabBar *mTabBar;
    TabsAPI *mTabsAPI;
    Ui::MainWindow *ui;
    int mAmountOpenedTabs;
};

#endif // MAINWINDOW_H
