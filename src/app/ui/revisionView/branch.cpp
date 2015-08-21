/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Volodymyr Kochyn  (vovakochyn@gmail.com)                      ***
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

#include "branch.h"
#include "revisionitem.h"

Branch::Branch(RevisionItem *pItem, const QString &pName) :
    mLast(pItem),
    mFirst(pItem),
    mName(pName)
{
    if (pItem)
    {
        addCommit(pItem);
    }
}

void Branch::addCommit(RevisionItem *pItem)
{
    if (pItem)
    {
        pItem->setParentBranch(this);
        mItems.append(pItem);
        mLast = pItem;
    }
}

RevisionItem *Branch::head() const
{
    return mLast;
}

RevisionItem *Branch::first() const
{
    return mFirst;
}

QString Branch::name() const
{
    return mName;
}

void Branch::setStartY(int pValue)
{
    mStartY = pValue;
}

int Branch::startY() const
{
    return mStartY;
}
