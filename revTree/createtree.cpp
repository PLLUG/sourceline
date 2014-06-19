#include "createtree.h"

CreateTree::CreateTree()
{
}

RevisionNode *CreateTree::create() const
{
    int revCount = 0;
    RevisionNode *root = createSimpleNode("Head", QString("%1").arg(revCount++));
    addCommit(root, createSimpleNode("first commit", QString("%1").arg(revCount++)));
    RevisionNode *branch = createSimpleNode("My brunch", QString("%1").arg(revCount++));
    root->children.last()->addChildren(branch);
    addCommit(root->children.last(), createSimpleNode("My brunch: second commit", QString("%1").arg(revCount++)));
    addCommit(root->children.last(), createSimpleNode("My brunch: third commit", QString("%1").arg(revCount++)));

    addCommit(root->children.last()->children.last(), createSimpleNode("My second brunch: first commit", QString("%1").arg(revCount++)));

    addCommit(root, createSimpleNode("second commit", QString("%1").arg(revCount++)));
    addCommit(root, createSimpleNode("third commit", QString("%1").arg(revCount++)));
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
        head->addChildren(commit);
    }
}
