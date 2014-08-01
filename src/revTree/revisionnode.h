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
    RevisionNode(const QString &message);

    int count() const;
    const RevisionNode *node(int rev) const;
    QVariant data(ItemDataRole role) const;
    void updateData();
    void setData(ItemDataRole role, const QVariant &data);

    int pos() const;
    bool isHeadInBranch() const;
    bool hasRevision(RevisionNode *r) const;

    void setRevId(const QString &id);
    QString revId() const;

    int row() const;

    void addChild(RevisionNode *node);
    void addBranch(RevisionNode *nodes);
    void mergeTo(RevisionNode *rev);

    RevisionNode *HEAD() const;

    RevisionNode *parent;
    RevisionNode *child;
    QList<RevisionNode *> branches;
    RevisionNodeItem *graphicsItem;
    RevisionNode *mMergeTo;

    bool operator ==(const RevisionNode &another);

private:
    QString _revId;
    QMap<ItemDataRole, QVariant> mData;
    QMap<QString, QVariant> mDrawData;
    int branchCount;
    bool isLast;
    int mPos;

    int branchNumber(RevisionNode *node) const;
    int nextBranchSize() const;
};

#endif // REVISIONNODE_H
