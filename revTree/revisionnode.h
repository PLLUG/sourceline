#ifndef REVISIONNODE_H
#define REVISIONNODE_H

#include <QString>
#include <QList>

class RevisionNodeItem;

class RevisionNode
{
public:
    RevisionNode();

    void setMessage(const QString &m);
    QString message() const;

    void setRevId(const QString &id);
    QString revId() const;

    int row() const;

    void addChild(RevisionNode *node);
    void addChildren(RevisionNode *nodes);

    RevisionNode *HEAD() const;

    RevisionNode *parent;
    RevisionNode *child;
    QList<RevisionNode *> children;
    RevisionNodeItem *graphicsItem;

private:
    QString _message;
    QString _revId;
};

#endif // REVISIONNODE_H
