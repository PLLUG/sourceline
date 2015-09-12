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

class Aggregator: public QObject
{
    Q_OBJECT

public:
    explicit Aggregator(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~Aggregator() {}

    /*!
     * \brief Set obj as children of Aggregator class.
     */
    void addObject(QObject *pObj)
    {
        if (!mContents.contains(pObj))
        {
            mContents.append(pObj);
        }
    }

    /*!
     *\brief Template getter.
     * Allow to get pointer on Aggregator's children.
     * If Aggregator doesn't have suitable children, getter returns null pointer.
     */
    template <typename T>
    T* object()
    {
        T * rObj = nullptr;
        for (QObject *o: mContents)
        {
            if((rObj = qobject_cast<T*>(o)))
            {
                break;
            }
        }
        return rObj;
    }

private:
    QObjectList mContents;
};




#endif // AGGREGATOR_H
