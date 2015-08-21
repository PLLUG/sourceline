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

#ifndef CREATETREE_H
#define CREATETREE_H

#include <QVector>

QT_FORWARD_DECLARE_CLASS(RevisionNode)

class CreateTree
{
public:
    CreateTree();

    RevisionNode *create() const;

private:
    RevisionNode *createSimpleNode(const QString &pMessage, const QString &pId) const;
    void addCommit(RevisionNode *pHead, RevisionNode *pCommit) const;
    void addBranch(RevisionNode *pFrom, RevisionNode *pTo) const;

    mutable QVector<RevisionNode*> mAllRevisions;
};

#endif // CREATETREE_H
