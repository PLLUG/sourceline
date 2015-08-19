/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Mykola Molochiy (molochiy@gmail.com)                          ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H

#include <QTabWidget>
#include "settings_dialog/settingsmanager.h"

class QWidget;
class Settings;
class ContentForTabWorkplace;
class SettingStorage;

namespace Ui {
class CustomTabBar;
}

class CustomTabBar : public QTabWidget
{
    Q_OBJECT

public:
    explicit CustomTabBar(SettingsManager *pSettingsManager, SettingStorage *pStorage, QWidget *parent = 0);
    ~CustomTabBar();

    void loadSettingsForTabs();

public slots:
    /*!
     * \brief Add New Workplace in mainwindow
     * \param Name of workplace
     */
    void slotAddNewWorkplace(const QString &pName);

    /*!
     * \brief Slot Close Workplace
     * \param pIndex - index of tab
     */
    void slotCloseWorkplace(int pIndex);
private slots:
    /*!
     * \brief Set All Tabs Invisible Except Current Tab
     * \param pIndex - index current tab
     */
    void setAllTabsInvisibleExceptCurrentTab(int pIndex);
private:
    Ui::CustomTabBar *ui;

    Settings *mSettings;
    SettingStorage *mStorage;
    SettingsManager *mSettingsManager;

private:
    ContentForTabWorkplace *getWidget(int pIndex);
};

#endif // CUSTOMTABBAR_H
