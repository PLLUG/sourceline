#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "contentfortabworkplace.h"
#include "settings_dialog/settingsmanager.h"

class TabsAPI;
class CustomTabBar;
class QMenu;
class SettingManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SettingsManager *pSettingsManager, SettingStorage *mStorage, QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QSystemTrayIcon *TrayIcon;
    QMenu *trayMenu;
    CustomTabBar *mTabBar;
    TabsAPI *mTabsAPI;
    int mAmountOpenedTabs;
    SettingsManager *mSettingsManager;

signals:
    void mysignal();

private:
    void resizeEvent(QResizeEvent *e);

private slots:

    /*!
     * \brief Activate icon
     */
    void iconActivated(QSystemTrayIcon::ActivationReason);

    /*!
     * \brief Close window
     */
    void CloseWindow();

    /*!
     * \brief slot Quit also close window
     */
    void slotQuit();

    /*!
     * \brief slotAddNewWorkplace add new worplace on window
     */
    void slotAddNewWorkplace();
};

#endif // MAINWINDOW_H
