#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
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
#include <QObject>
#include "guidefs.h"
#include <QMap>
#include <QAction>
#include <QString>
#include <QList>

class ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject *parent = 0);
    void addBack(MenuGroups pMenuGroups, QString pCategory, QAction *pAction);
    void addAt(MenuGroups pMenuGroups, unsigned pIndex , QString pCategory, QAction *pAction);
    QList<QAction *> actions(MenuGroups pMenuGroups) const;
signals:

public slots:
private:
    QMap<MenuGroups, QList<QAction *> > mActions;

};

#endif // ACTIONMANAGER_H
