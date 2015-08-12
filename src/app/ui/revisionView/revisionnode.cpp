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

#include "revisionnode.h"
#include <QDebug>

RevisionNode::RevisionNode() :
    mParent(0),
    mChild(0),
    mGraphicsItem(0),
    mMergeTo(0),
    mPos(0)
{
    mBranchCount = 0;
    mIsLast = true;
}

RevisionNode::RevisionNode(const QString &pMessage)
{
    static int lRev = 0;
    setData(IDR_DisplayRole, pMessage);
    setRevId(QString().setNum(lRev++));
    mPos = 0;
}

int RevisionNode::count() const
{
    int rCount = 0;
    const RevisionNode *lHead = this;
    while (lHead)
    {
        ++rCount;
        for (int i = 0; i < lHead->mBranches.size(); ++i)
        {
            rCount += lHead->mBranches.at(i)->count();
        }
        lHead = lHead->mChild;
    }
    return rCount;
}

const RevisionNode *RevisionNode::node(int pRev) const
{
    const RevisionNode *rNode = this;
    QString lRevId = QString().setNum(pRev);
    while (rNode && (rNode->revId() != lRevId))
    {
        if (!rNode->mBranches.isEmpty())
        {
            for (int i = 0; i < rNode->mBranches.size(); ++i)
            {
                const RevisionNode * lTmpNode = rNode->mBranches.at(i)->node(pRev);
                if (lTmpNode)
                {
                    return lTmpNode;
                }
            }
        }
        rNode = rNode->mChild;
    }
    return rNode;
}

QVariant RevisionNode::data(ItemDataRole pRole) const
{
    if (mData.contains(pRole))
    {
        return mData.value(pRole);
    }
    else
    {
        return QVariant();
    }
}

void RevisionNode::updateData()
{
    mDrawData.insert("pos", mPos);
    mDrawData.insert("branches", 0);
    mDrawData.insert("children", mBranchCount);
    mDrawData.insert("last", mIsLast);
    setData(IDR_DrawRole, mDrawData);
}

void RevisionNode::setData(RevisionNode::ItemDataRole pRole, const QVariant &pData)
{
    mData[pRole] = pData;
}

int RevisionNode::pos() const
{
    int rPos = 0;
//    const RevisionNode *node = this;
//    while ( node->parent )
//    {
//        ++p;
//        node = node->parent;
//    }
//    p += branchNumber(const_cast<RevisionNode*>(this));
    return rPos;
}

bool RevisionNode::isHeadInBranch() const
{
    return (mChild == 0);
}

bool RevisionNode::hasRevision(RevisionNode *pRevision) const
{
    const RevisionNode *lNode = this;
    while (lNode)
    {
        if (lNode == pRevision)
        {
            return true;
        }
        lNode = lNode->mChild;
    }
    return false;
}

void RevisionNode::setRevId(const QString &pId)
{
    mRevId = pId;
}

QString RevisionNode::revId() const
{
    return mRevId;
}

int RevisionNode::row() const
{
    if (mParent)
    {
        return mParent->mBranches.indexOf(const_cast<RevisionNode*>(this));
    }
    else
    {
        return 0;
    }
}

void RevisionNode::addChild(RevisionNode *pNode)
{
    if (pNode)
    {
        mChild = pNode;
        mChild->mParent = mParent;
    }
}

void RevisionNode::addBranch(RevisionNode *pNodes)
{
    if (pNodes)
    {
        mBranches.append(pNodes);
        pNodes->mParent = this;
    }
}

void RevisionNode::mergeTo(RevisionNode *pRev)
{
    mMergeTo = pRev;
}

RevisionNode *RevisionNode::HEAD() const
{
    RevisionNode *rHead = mChild;
    while (rHead != 0)
    {
        if (rHead->mChild == 0)
        {
            break;
        }
        rHead = rHead->mChild;
    }
    if (!rHead)
    {
        rHead = const_cast<RevisionNode *>(this);
    }
    return rHead;
}

bool RevisionNode::operator ==(const RevisionNode &pAnother)
{
    return mRevId == pAnother.mRevId;
}

int RevisionNode::branchNumber(RevisionNode *pNode) const
{
    if (pNode->mParent)
    {
        RevisionNode *lTmpNode;
        for (int i = 0; i < pNode->mParent->mBranches.size(); ++i)
        {
            lTmpNode = pNode->mParent->mBranches.at(i);
            while (lTmpNode)
            {
                if (lTmpNode == pNode)
                {
                    return i;
                }
                lTmpNode = lTmpNode->mChild;
            }
        }
    }
    return 0;
}

int RevisionNode::nextBranchSize() const
{
    //TODO: check coments
    RevisionNode *lNode = mParent;
    Q_UNUSED(lNode)
    RevisionNode *lCurrentItem = const_cast<RevisionNode*>(this);
    Q_UNUSED(lCurrentItem)
    int rCounter = 0;
//    while (node)
//    {
//        if (!node->branches.isEmpty())
//        {
//            bool cont = false;
//            for (int i = 0; i < node->branches.size(); ++i)
//            {
//                if (!node->branches.at(i)->hasRevision(currentItem))
//                {
//                    if ((node->branches.at(i)->HEAD()->revId().toInt() > revId().toInt()) && cont)
//                        counter++;
//                }
//                else
//                {
//                    cont = true;
//                }
//            }
//        }
//        currentItem = node;
//        node = node->parent;
//    }
    return rCounter;
}
