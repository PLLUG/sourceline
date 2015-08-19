#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStringList>
#include "contentfortabworkplace.h"
#include "settings_dialog/settingsmanager.h"

class TabsAPI;
class CustomTabBar;
class QMenu;
class SettingManager;
class Settings;
class SettingStorage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QStringList openedTabs READ openedTabs WRITE setOpenedTabs NOTIFY openedTabsChanged)

public:
    explicit MainWindow(SettingsManager *pSettingsManager, SettingStorage *pStorage, QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

    QStringList openedTabs() const;

public slots:
    void setOpenedTabs(QVariant pOpenedTabs);

private:
    QSystemTrayIcon *TrayIcon;
    QMenu *trayMenu;
    CustomTabBar *mTabBar;
    TabsAPI *mTabsAPI;
    int mAmountOpenedTabs;
    Settings *mSettings;
    SettingStorage *mStorage;
    SettingsManager *mSettingsManager;
    mutable QStringList mListOpenedTabs;
    void resizeEvent(QResizeEvent *e);

    void closeEvent(QCloseEvent *pEvent);

signals:
    void mysignal();

    void openedTabsChanged(QStringList openedTabs);

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
