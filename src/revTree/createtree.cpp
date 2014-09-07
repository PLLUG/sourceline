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
#include <QDebug>

CreateTree::CreateTree()
{
}

RevisionNode *CreateTree::create() const
{
    int revCount = 0;
    RevisionNode *root = createSimpleNode("master", QString("%1").arg(revCount++));
    mAllRevisions.append(root);
    addCommit(root->HEAD(), createSimpleNode("Master: first commit", QString("%1").arg(revCount++)));
    RevisionNode *branch = createSimpleNode("test branch #1: first commit", QString("%1").arg(revCount++));
    addBranch(root->HEAD(), branch);
    addBranch(root->HEAD(), createSimpleNode("test branch #2: first commit", QString("%1").arg(revCount++)));
    //RevisionNode *n = root->HEAD();

    addCommit(branch->HEAD(), createSimpleNode("test branch #1: second commit", QString("%1").arg(revCount++)));

    addCommit(root->HEAD()->branches.at(1)->HEAD(), createSimpleNode("test branch #2: second commit", QString("%1").arg(revCount++)));
    addCommit(branch->HEAD(), createSimpleNode("test branch #1: third commit", QString("%1").arg(revCount++)));

    addBranch(branch->HEAD(), createSimpleNode("test branch #3: first commit", QString("%1").arg(revCount++)));

    addCommit(branch->HEAD(), createSimpleNode("test branch #1: fourth commit", QString("%1").arg(revCount++)));

    addCommit(root->HEAD(), createSimpleNode("master: second commit merged from test branch #1", QString("%1").arg(revCount++)));

    //branch->HEAD()->mergeTo(root->HEAD());

    addCommit(root->HEAD(), createSimpleNode("master: third commit", QString("%1").arg(revCount++)));
    //addBranch(n, createSimpleNode("test branch #1_1: first commit", QString("%1").arg(revCount++)));
    foreach (RevisionNode *node, mAllRevisions)
        node->updateData();
    return root;
}

RevisionNode *CreateTree::createSimpleNode(const QString &message, const QString &id) const
{
    RevisionNode *node = new RevisionNode;
    node->setData(RevisionNode::IDR_DisplayRole, message);
    node->setRevId(id);
    mAllRevisions.append(node);
    return node;
}

void CreateTree::addCommit(RevisionNode *head, RevisionNode *commit) const
{
    if ( head && commit ) {
        head->addChild(commit);
    }
}

void CreateTree::addBranch(RevisionNode *from, RevisionNode *to) const
{
    if ( from && to )
        from->addBranch(to);
}
