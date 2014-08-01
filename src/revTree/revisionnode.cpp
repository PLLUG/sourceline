#include "revisionnode.h"
#include <QDebug>

RevisionNode::RevisionNode() :
    parent(0),
    child(0),
    graphicsItem(0),
    mMergeTo(0),
    mPos(0)
{
}

RevisionNode::RevisionNode(const QString &message)
{
    static int rev = 0;
    setData(IDR_DisplayRole, message);
    setRevId(QString().setNum(rev++));
    mPos = 0;
}

int RevisionNode::count() const
{
    int count = 0;
    const RevisionNode *ch = this;
    while ( ch )
    {
        ++count;
        for (int i = 0; i < ch->branches.size(); ++i)
            count += ch->branches.at(i)->count();
        ch = ch->child;
    }
    return count;
}

const RevisionNode *RevisionNode::node(int rev) const
{
    const RevisionNode *node = this;
    QString revId = QString().setNum(rev);
    while ( node && node->revId() != revId )
    {
        if ( !node->branches.isEmpty() )
        {
            for (int i = 0; i < node->branches.size(); ++i)
            {
                const RevisionNode * tmp = node->branches.at(i)->node(rev);
                if ( tmp )
                    return tmp;
            }
        }
        node = node->child;
    }
    return node;
}

QVariant RevisionNode::data(ItemDataRole role) const
{
    if (mData.contains(role))
        return mData.value(role);
    return QVariant();
}

void RevisionNode::updateData()
{
    mDrawData.insert("pos", mPos);
    mDrawData.insert("branches", 0);
    mDrawData.insert("children", branchCount);
    mDrawData.insert("last", isLast);
    setData(IDR_DrawRole, mDrawData);
}

void RevisionNode::setData(RevisionNode::ItemDataRole role, const QVariant &data)
{
    mData[role] = data;
}

int RevisionNode::pos() const
{
    int p = 0;
//    const RevisionNode *node = this;
//    while ( node->parent )
//    {
//        ++p;
//        node = node->parent;
//    }
//    p += branchNumber(const_cast<RevisionNode*>(this));
    return p;
}

bool RevisionNode::isHeadInBranch() const
{
    return (child == 0);
}

bool RevisionNode::hasRevision(RevisionNode *r) const
{
    const RevisionNode *node = this;
    while (node)
    {
        if ( node == r )
            return true;
        node = node->child;
    }
    return false;
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
        return parent->branches.indexOf(const_cast<RevisionNode*>(this));
    }
    return 0;
}

void RevisionNode::addChild(RevisionNode *node)
{
    if ( node )
    {
        child = node;
        child->parent = parent;
    }
}

void RevisionNode::addBranch(RevisionNode *nodes)
{
    if ( nodes ) {
        branches.append(nodes);
        nodes->parent = this;
    }
}

void RevisionNode::mergeTo(RevisionNode *rev)
{
    mMergeTo = rev;
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

bool RevisionNode::operator ==(const RevisionNode &another)
{
    return _revId == another._revId;
}

int RevisionNode::branchNumber(RevisionNode *node) const
{
    if ( node->parent )
    {
        RevisionNode *tmp;
        for (int i = 0; i < node->parent->branches.size(); ++i)
        {
            tmp = node->parent->branches.at(i);
            while ( tmp )
            {
                if ( tmp == node )
                    return i;
                tmp = tmp->child;
            }
        }
    }
    return 0;
}

int RevisionNode::nextBranchSize() const
{
    RevisionNode *node = parent;
    RevisionNode *currentItem = const_cast<RevisionNode*>(this);
    int counter = 0;
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
    return counter;
}
