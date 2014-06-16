#ifndef CREATETREE_H
#define CREATETREE_H

#include "revisionnode.h"

class CreateTree
{
public:
    CreateTree();

    RevisionNode *create() const;

private:
    RevisionNode *createSimpleNode(const QString &message, const QString &id) const;
    void addCommit(RevisionNode *head, RevisionNode *commit) const;
};

#endif // CREATETREE_H
