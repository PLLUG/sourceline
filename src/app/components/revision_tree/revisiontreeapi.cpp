#include "revisiontreeapi.h"

RevisionTreeAPI::RevisionTreeAPI(RevisionTree &revisionTree, /*CommandManager &commandManager,*/ QObject *parent):
    IRevisionTreeAPI(parent)
  ,mRevisionTree(revisionTree)
//  ,mCommandManager(commandManager)
{
}

void RevisionTreeAPI::addNode(QString pParentID, QString pNodeId)
{
    mRevisionTree.addNode(pParentID.toStdString(),pNodeId.toStdString());
}

void RevisionTreeAPI::putProperty(QString pRecepientId, QString property, QVariant value)
{
    mRevisionTree.putProperty(pRecepientId.toStdString(),property.toStdString(),value);
}
