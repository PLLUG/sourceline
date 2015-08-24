#ifndef PLUGINDESCRIPTION_H
#define PLUGINDESCRIPTION_H
/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Priyma Yuriy (priymayuriy@gmail.com)                          ***
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
#include <QString>
#include <QHash>

#include "pluginmanager_global.h"

class PLUGINMANAGERSHARED_EXPORT PluginInfo
{
public:
    PluginInfo(QString pPluginId, QString pVer, QString pDescr, QString pCategory, QHash<QString, QString> pAdditionalInfo);
    PluginInfo();
    //TASK : plugin id SLOULD NOT be the same as filename - there are some differences in library
    // namings in Linux and Windows. Plugin id SHOULD BE unique! like org.PLLUG.git-plugin
    QString pluginId() const;
    QString ver() const;
    QString description() const;
    QString category() const ;
    QHash<QString, QString> additionalInfo() const;
private:
    QString mPluginId;
    QString mVer;
    QString mDescr;
    QString mCategory;
    QHash<QString, QString> mAdditionalInfo;
};

#endif // PLUGINDESCRIPTION_H
