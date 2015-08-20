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

#include "creator.h"
#include "revisionitem.h"
#include "branch.h"

#include <QVector>
#include <QDebug>

Creator::Creator() :
    mCurrent(0)
{
    addBranch(new RevisionItem("init master"), "master");
    addCommit(new RevisionItem("master/first commit"));
    addCommit(new RevisionItem("master/second commit"));
    addBranch(new RevisionItem("Branch: init"), "test branch");
    switchTo(mBranches.at(0));
    addCommit(new RevisionItem("master/third commit"));
}

GraphField *Creator::field()
{
    return &mField;
}

RevisionItem *Creator::item(int pPosition) const
{
    foreach(RevisionItem *lItem, mItems)
    {
        if (lItem->y() == pPosition)
            return lItem;
    }
    return 0;
}

void Creator::addCommit(RevisionItem *pCommit)
{
    if (mCurrent)
    {
        mField.addCommit(pCommit, mCurrent->head());
        mCurrent->addCommit(pCommit);
    }
    mItems.append(pCommit);
}

void Creator::addBranch(RevisionItem *pBranch, const QString &pName)
{
    mBranches.append(new Branch(pBranch, pName));
    mField.addBranch(pBranch);
    if (mCurrent && mCurrent->head())
    {
        mCurrent->head()->addBranch(pBranch);
        mBranches.last()->setStartY(mCurrent->head()->y());
    }
    mCurrent = mBranches.last();
    mItems.append(pBranch);
}

void Creator::merge(RevisionItem *pFrom, RevisionItem *pTo)
{
    Q_UNUSED(pFrom)
    Q_UNUSED(pTo)
    //
}

void Creator::switchTo(Branch *pBranch)
{
    mCurrent = pBranch;
}

QList<QVariant> Creator::branchesBefore(RevisionItem *pItem) const
{
    QList<QVariant> rList;
    foreach (Branch *lBranch, mBranches)
    {
        if (pItem->parentBranch() != lBranch)
        {
            if (lBranch->head())
            {
                if (lBranch->head()->x() < pItem->x())
                {
                    if (lBranch->head()->y() > pItem->y())
                    {
                        rList.append(lBranch->head()->x());
                    }
                }
            }
        }
    }
    return rList;
}

QList<QVariant> Creator::branchesAfter(RevisionItem *pItem) const
{
    QList<QVariant> rList;
    foreach (Branch *lBranch, mBranches)
    {
        if (pItem->parentBranch() != lBranch)
        {
            if (lBranch->head())
            {
                if (lBranch->head()->x() > pItem->x())
                {
                    if ((lBranch->startY() < pItem->y())
                        && (lBranch->head()->y() > pItem->y()))
                    {
                        rList.append(lBranch->head()->x());
                    }
                }
            }
        }
    }
    return rList;
}

QList<QVariant> Creator::brPos(RevisionItem *pItem) const
{
    QList<QVariant> rList;
    foreach (RevisionItem *lBranch, pItem->branches())
    {
        rList.append(lBranch->x());
    }
    return rList;
}
