#ifndef REVISIONTREEAPI_H
#define REVISIONTREEAPI_H

#include "irevisiontreeapi.h"
#include "revisiontree.h"
class CommandManager;

class RevisionTreeAPI : public IRevisionTreeAPI
{
    Q_OBJECT
public:
    explicit RevisionTreeAPI(RevisionTree &revisionTree, /*CommandManager &commandManager,*/ QObject *parent = 0);

public slots:
    void addNode(QString pParentID, QString pNodeId) override final;
    void putProperty(QString pRecepientId, QString property, QVariant value) override final;

private:
    RevisionTree &mRevisionTree;
//    CommandManager &mCommandManager;
};

#endif // REVISIONTREEAPI_H
