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

RevisionItem *Creator::item(int position) const
{
    foreach(RevisionItem *i, mItems)
    {
        if (i->y() == position)
            return i;
    }
    return 0;
}

void Creator::addCommit(RevisionItem *c)
{
    if (mCurrent)
    {
        mField.addCommit(c, mCurrent->head());
        mCurrent->addCommit(c);
    }
    mItems.append(c);
}

void Creator::addBranch(RevisionItem *b, const QString &name)
{
    mBranches.append(new Branch(b, name));
    mField.addBranch(b);
    if (mCurrent && mCurrent->head())
    {
        mCurrent->head()->addBranch(b);
        mBranches.last()->setStartY(mCurrent->head()->y());
    }
    mCurrent = mBranches.last();
    mItems.append(b);
}

void Creator::switchTo(Branch *b)
{
    mCurrent = b;
}

QList<QVariant> Creator::branchesBefore(RevisionItem *i) const
{
    QList<QVariant> ret;
    foreach (Branch *b, mBranches)
    {
        if (i->parentBranch() != b)
            if (b->head())
            {
                if (b->head()->x() < i->x())
                    if (b->head()->y() > i->y())
                        ret.append(b->head()->x());
            }
    }
    return ret;
}

QList<QVariant> Creator::branchesAfter(RevisionItem *i) const
{
    QList<QVariant> ret;
    foreach (Branch *b, mBranches)
    {
        if (i->parentBranch() != b)
            if (b->head())
            {
                if (b->head()->x() > i->x())
                    if ((b->startY() < i->y())
                        && (b->head()->y() > i->y()))
                        ret.append(b->head()->x());
            }
    }
    return ret;
}

QList<QVariant> Creator::brPos(RevisionItem *i) const
{
    QList<QVariant> ret;
    foreach (RevisionItem *b, i->branches())
    {
        ret.append(b->x());
    }
    return ret;
}
