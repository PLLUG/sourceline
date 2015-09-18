#ifndef REVISIONTREEAPIINTERFACE
#define REVISIONTREEAPIINTERFACE

#endif // REVISIONTREEAPIINTERFACE

#include "irevisiontreeapi.h"

class RevisionTreeInterface : public IRevisionTreeAPI
{
    Q_OBJECT
public:
    explicit RevisionTreeInterface(QObject *parent = 0) :
        IRevisionTreeAPI(parent){}

public slots:
    void addNode(QString pParentID, QString pNodeInfo) override final
    {
        emit invokeCommand("addNode(QString, QString);", pParentID, pNodeInfo);
    }

    void putProperty(QString pRecepientId, QString property, QVariant value) override final
    {
        emit invokeCommand("putProperty(QString, QString, QVariant)", pRecepientId, property, value);
    }
};
