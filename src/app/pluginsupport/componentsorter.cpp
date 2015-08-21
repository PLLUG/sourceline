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
#include "componentsorter.h"

#include "supliers/componentsupplier.h"
#include "plugininfo.h"
#include <string>

ComponentSorter::ComponentSorter(QObject *parent) :
    QObject(parent)
{
}

void ComponentSorter::setComponents(QObjectList pComponents, const PluginInfo &pPluginInfo)
{
    foreach (QObject *lComponent, pComponents)
    {
        ComponentSupplier *lSupplier = supplierForComponent(lComponent);
        if (lSupplier)
        {
            lSupplier->supply(lComponent, pPluginInfo);
        }
    }
}

void ComponentSorter::addSupplier(ComponentSupplier *pSupplier)
{
    mSupplierByClassName.insert(pSupplier->className(), pSupplier);
}


ComponentSupplier *ComponentSorter::supplierForComponent(QObject *pComponent)
{
    ComponentSupplier *rSupplier = 0;

    foreach (QString lClassName, mSupplierByClassName.keys())
    {
        if (pComponent->inherits(lClassName.toUtf8().data()))
        {
            rSupplier = mSupplierByClassName.value(lClassName);
        }
    }

    return rSupplier;
}
