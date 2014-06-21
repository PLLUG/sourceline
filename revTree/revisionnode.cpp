#include "revisionnode.h"
#include <QDebug>

RevisionNode::RevisionNode() :
    parent(0),
    child(0),
    graphicsItem(0)
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

void RevisionNode::addChild(RevisionNode *node)
{
    if ( node )
    {
        child = node;
        child->parent = this;
    }
}

void RevisionNode::addChildren(RevisionNode *nodes)
{
    if ( nodes ) {
        children.append(nodes);
        nodes->parent = this;
    }
}

RevisionNode *RevisionNode::HEAD() const
{
    RevisionNode *head = child;
    while ( head != 0 )
    {
        if ( head->child == 0 )
            break;
        head = head->child;
    }
    if ( !head )
        head = const_cast<RevisionNode *>(this);
    return head;
}
