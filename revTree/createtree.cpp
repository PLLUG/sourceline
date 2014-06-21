#include "createtree.h"
#include <QDebug>

CreateTree::CreateTree()
{
}

RevisionNode *CreateTree::create() const
{
    int revCount = 0;
    RevisionNode *root = createSimpleNode("Head", QString("%1").arg(revCount++));
    addCommit(root->HEAD(), createSimpleNode("first commit", QString("%1").arg(revCount++)));
    RevisionNode *branch = createSimpleNode("My brunch", QString("%1").arg(revCount++));
    addBranch(root->HEAD(), branch);

    addCommit(branch->HEAD(), createSimpleNode("My brunch: second commit", QString("%1").arg(revCount++)));
    addCommit(branch->HEAD(), createSimpleNode("My brunch: third commit", QString("%1").arg(revCount++)));

    addBranch(branch->HEAD(), createSimpleNode("My second brunch: first commit", QString("%1").arg(revCount++)));

    addCommit(root->HEAD(), createSimpleNode("second commit", QString("%1").arg(revCount++)));
    addCommit(root->HEAD(), createSimpleNode("third commit", QString("%1").arg(revCount++)));
    return root;
}

RevisionNode *CreateTree::createSimpleNode(const QString &message, const QString &id) const
{
    RevisionNode *node = new RevisionNode;
    node->setMessage(message);
    node->setRevId(id);
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
        from->addChildren(to);
}
