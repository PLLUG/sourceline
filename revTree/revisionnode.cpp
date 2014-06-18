#include "revisionnode.h"

RevisionNode::RevisionNode() :
    parent(0)
{
}

void RevisionNode::setMessage(const QString &m)
{
    _message = m;
}

QString RevisionNode::message() const
{
    return _message;
}

void RevisionNode::setRevId(const QString &id)
{
    _revId = id;
}

QString RevisionNode::revId() const
{
    return _revId;
}

int RevisionNode::row() const
{
    if ( parent )
    {
        return parent->children.indexOf(const_cast<RevisionNode*>(this));
    }
    return 0;
}

//void RevisionNode::addChild(RevisionNode *node)
//{
//    if ( node )
//    {
//        child = node;
//        node->parent = this;
//    }
//}

void RevisionNode::addChildren(RevisionNode *nodes)
{
    if ( nodes ) {
        children.append(nodes);
        nodes->parent = this;
    }
}
