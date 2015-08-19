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

#ifndef TABSAPI_H
#define TABSAPI_H

#include <QWidget>
#include <QObject>
#include "settings_dialog/settingsmanager.h"

class CustomTabBar;

/*!
 * \brief The PageManager class handles all pages for repositories.
 */
class TabsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TabsAPI(QObject *parent = 0);
    /*!
     * \brief Get current index of tab
     * \param pTabBar - tabBar where is this tab
     * \return index current tab
     */
    int getCurrentIndex(CustomTabBar *pTabBar);
    /*!
     * \brief get count tabs
     * \param pTabBar - tab bar
     * \return amount tabs
     */
    int getCountTabs(CustomTabBar *pTabBar);

    /*!
     * \brief Get widget of current tab
     * \param pTabBar
     * \return Returns a pointer to the page currently being displayed by the tab dialog.
     */
    QWidget* getCurrentWidget(CustomTabBar *pTabBar);

    /*!
     * \brief Get widget of tab with index
     * \param pTabBar
     * \param index of tab
     * \return Returns the tab page at index position index
     */
    QWidget* getWidget(CustomTabBar *pTabBar, int pIndex);

    void loadSettingsForTabs(CustomTabBar *pTabBar);

    QString getNameOfTabById(CustomTabBar *pTabBar, int pId) const;

public slots:
    /*!
     * \brief Add New Workplace in main menu
     * \param lName Name of tab
     */
    void slotAddNewWorkplace(CustomTabBar *pTabBar, const QString &pName);

    /*!
     * \brief Slot close Workplace
     * \param pTabBar - tabbar
     * \param pIndex - index of tab
     */
    void slotCloseWorkplace(CustomTabBar *pTabBar, int pIndex);
};

#endif // TABSAPI_H
