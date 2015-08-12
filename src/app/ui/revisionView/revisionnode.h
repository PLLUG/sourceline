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

#ifndef REVISIONNODE_H
#define REVISIONNODE_H

#include <QString>
#include <QList>
#include <QVariant>

class RevisionNodeItem;
class RevisionTree;

class RevisionNode
{
    friend class RevisionTree;
public:
    enum ItemDataRole { IDR_DisplayRole,
                        IDR_DrawRole
                      };
    RevisionNode();
    explicit RevisionNode(const QString &pMessage);

    int count() const;
    const RevisionNode *node(int pRev) const;
    QVariant data(ItemDataRole pRole) const;
    void updateData();
    void setData(ItemDataRole pRole, const QVariant &pData);

    int pos() const;
    bool isHeadInBranch() const;
    bool hasRevision(RevisionNode *pRevision) const;

    void setRevId(const QString &pId);
    QString revId() const;

    int row() const;

    void addChild(RevisionNode *pNode);
    void addBranch(RevisionNode *pNodes);
    void mergeTo(RevisionNode *pRev);

    RevisionNode *HEAD() const;

    RevisionNode *mParent;
    RevisionNode *mChild;
    QList<RevisionNode *> mBranches;
    RevisionNodeItem *mGraphicsItem;
    RevisionNode *mMergeTo;

    bool operator ==(const RevisionNode &pAnother);

private:
    QString mRevId;
    QMap<ItemDataRole, QVariant> mData;
    QMap<QString, QVariant> mDrawData;
    int mBranchCount;
    bool mIsLast;
    int mPos;

    int branchNumber(RevisionNode *pNode) const;
    int nextBranchSize() const;
};

#endif // REVISIONNODE_H
