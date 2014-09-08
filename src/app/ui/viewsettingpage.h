/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
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

#ifndef VIEWSETTINGPAGE_H
#define VIEWSETTINGPAGE_H

#include "settingspage.h"
#include "settings.h"
#include <QVariant>
#include <QDebug>
#include <QLayout>
#include "ui_viewsettingpage.h"

namespace Ui {
class MainWindow;
}

class ViewSettingPage : public SettingsPage
{
    Q_OBJECT
public:
    explicit ViewSettingPage(Settings *pSettings, QWidget *parent = 0);
    ~ViewSettingPage();

    void setMainUi(Ui::MainWindow *lMainUi);

signals:
    void signalGetSettings(QString pPath);

private slots:
    void slotBtnOpen();

public slots:
    void slotFileViewChanged(QVariant pValue);
    void slotEditorViewChanged(QVariant pValue);
    void slotRevTreeChanged(QVariant pValue);
    void slotConsoleChanged(QVariant pValue);
    void slotTreeChanged(QVariant pValue);
    void slotConsolePath(QVariant pValue);

private:
    Ui::Form *mDialogUi;
    Ui::MainWindow *mMainUi;
    QString consolePath;

};

#endif // VIEWSETTINGPAGE_H
