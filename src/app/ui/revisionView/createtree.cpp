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

#include "createtree.h"
#include "revisionnode.h"

#include <QDebug>

CreateTree::CreateTree()
{
}

RevisionNode *CreateTree::create() const
{
    int lRevCount = 0;
    RevisionNode *rRoot = createSimpleNode("master", QString("%1").arg(lRevCount++));
    mAllRevisions.append(rRoot);
    addCommit(rRoot->HEAD(), createSimpleNode("Master: first commit", QString("%1").arg(lRevCount++)));
    RevisionNode *lBranch = createSimpleNode("test branch #1: first commit", QString("%1").arg(lRevCount++));
    addBranch(rRoot->HEAD(), lBranch);
    addBranch(rRoot->HEAD(), createSimpleNode("test branch #2: first commit", QString("%1").arg(lRevCount++)));
    //RevisionNode *n = root->HEAD();

    addCommit(lBranch->HEAD(), createSimpleNode("test branch #1: second commit", QString("%1").arg(lRevCount++)));

    addCommit(rRoot->HEAD()->mBranches.at(1)->HEAD(), createSimpleNode("test branch #2: second commit", QString("%1").arg(lRevCount++)));
    addCommit(lBranch->HEAD(), createSimpleNode("test branch #1: third commit", QString("%1").arg(lRevCount++)));

    addBranch(lBranch->HEAD(), createSimpleNode("test branch #3: first commit", QString("%1").arg(lRevCount++)));

    addCommit(lBranch->HEAD(), createSimpleNode("test branch #1: fourth commit", QString("%1").arg(lRevCount++)));

    addCommit(rRoot->HEAD(), createSimpleNode("master: second commit merged from test branch #1", QString("%1").arg(lRevCount++)));

    //branch->HEAD()->mergeTo(root->HEAD());

    addCommit(rRoot->HEAD(), createSimpleNode("master: third commit", QString("%1").arg(lRevCount++)));
    //addBranch(n, createSimpleNode("test branch #1_1: first commit", QString("%1").arg(revCount++)));
    foreach (RevisionNode *lNode, mAllRevisions)
        lNode->updateData();
    return rRoot;
}

RevisionNode *CreateTree::createSimpleNode(const QString &pMessage, const QString &pId) const
{
    RevisionNode *rNode = new RevisionNode;
    rNode->setData(RevisionNode::IDR_DisplayRole, pMessage);
    rNode->setRevId(pId);
    mAllRevisions.append(rNode);
    return rNode;
}

void CreateTree::addCommit(RevisionNode *pHead, RevisionNode *pCommit) const
{
    if (pHead && pCommit)
    {
        pHead->addChild(pCommit);
    }
}

void CreateTree::addBranch(RevisionNode *pFrom, RevisionNode *pTo) const
{
    if (pFrom && pTo)
    {
        pFrom->addBranch(pTo);
    }
}
