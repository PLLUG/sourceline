#ifndef AGGREGATOR_H
#define AGGREGATOR_H

/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***                 Mykhailo Voronovskii (mvoronovskii96@gmail.com)          ***
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
#include <iterator>
#include <QtAlgorithms>
#include "pluginsupport/componentsorter.h"

class Aggregator: public QObject
{
    Q_OBJECT

public:
    Aggregator(QObject *obj = nullptr);
    ~Aggregator();
    void setObject(QObject *obj);

    template <typename T>
    T* object();
};

template <typename T>
T* Aggregator::object()
{
    QObjectList childrens = this->children();
    for(int i = 0; i < childrens.count(); i++)
    {
        T *ob = qobject_cast<T*>(childrens[i]);
        if(T *ob = qobject_cast<T*>(childrens[i]))
        {
            return ob;
        }
        else
        {
            return nullptr;
        }
    }
}

#endif // AGGREGATOR_H
