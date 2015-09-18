#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStringList>
#include "settings_dialog/settingsmanager.h"
#include "contentfortab.h"

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

    QStringList openedTabs() const;
    Ui::MainWindow *getUi() const;

public slots:
    void setOpenedTabs(QVariant pOpenedTabs);

signals:
    void openedTabsChanged(QStringList openedTabs);

protected:
    void closeEvent(QCloseEvent *) override final;

private slots:

    /*!
     * \brief Activate icon
     */
    void iconActivated(QSystemTrayIcon::ActivationReason);

    /*!
     * \brief Close window
     */
    void slotCloseWindow();

    /*!
     * \brief slot Quit also close window
     */
    void slotQuit();

    /*!
     * \brief slotAddNewWorkplace add new worplace on window
     */
    void slotAddNewWorkplace();

private:
    QSystemTrayIcon *mTrayIcon;
    QMenu *mTrayMenu;
    CustomTabBar *mTabBar;
    TabsAPI *mTabsAPI;
    Ui::MainWindow *ui;
    int mAmountOpenedTabs;
    SettingStorage *mStorage;
    SettingsManager *mSettingsManager;
    Settings *mSettings;
    mutable QStringList mListOpenedTabs;
};

#endif // MAINWINDOW_H
