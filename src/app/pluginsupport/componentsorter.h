#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
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
#include <QMap>

class ComponentSupplier;
class ComponentSorter : public QObject
{
    Q_OBJECT
public:
    explicit ComponentSorter(QObject *parent = 0);

    void setComponents(int pCategory, QObjectList pComponents);
    void addSupplier(QString pName, ComponentSupplier * pSupplier);
private:
    ComponentSupplier *supplierForComponent(QObject *pComponent);

private:
    QMap<QString, ComponentSupplier*> mSupplierByClassName;
};

#endif // COMPONENTMANAGER_H