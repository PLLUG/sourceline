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

#ifndef GREATOR_H
#define GREATOR_H

#include "graphfield.h"
#include "revisionitem.h"
#include "branch.h"
#include <QVariant>

class Creator
{
public:
    Creator();

    GraphField* field() { return &mField; }
    RevisionItem* item(int position) const;

    void addCommit(RevisionItem *c);
    void addBranch(RevisionItem *b, const QString &name);

    void switchTo(Branch *b);

    QList<QVariant> branchesBefore(RevisionItem *i) const;
    QList<QVariant> branchesAfter(RevisionItem *i) const;
    QList<QVariant> brPos(RevisionItem *i) const;

private:
    QList<RevisionItem*> mItems;
    QList<Branch*> mBranches;
    GraphField mField;
    Branch *mCurrent;
};

#endif // GREATOR_H
