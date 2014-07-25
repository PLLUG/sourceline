#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

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

#include "pluginsettings.h"

#include <QWidget>
#include <QIcon>
#include <QDebug>

class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(PluginSettings *pSettings, QWidget *parent = 0);
    QString name() const;
    QIcon icon() const;
    PluginSettings *settings() const;

public slots:
    void slotApply();
    void slotCancel();

protected:
    void setName(const QString& pName);
    void setIcon(const QIcon& pIcon);

private:
    QString mName;
    QIcon mIcon;
    PluginSettings *mSettings;

};

#endif // SETTINGSPAGE_H