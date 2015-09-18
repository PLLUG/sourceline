#ifndef IREVISIONTREEAPI_H
#define IREVISIONTREEAPI_H

#include <QObject>
#include <QVariant>
#include "apibase.h"

class IRevisionTreeAPI : public ApiBase
{
    Q_OBJECT
public:
    explicit IRevisionTreeAPI(QObject *parent = nullptr) : ApiBase(parent) {}

public slots:
    virtual void addNode(QString pParentID, QString pNodeInfo)= 0;
    virtual void putProperty(QString pRecepientId, QString property, QVariant value) = 0;
};

#endif // IREVISIONTREEAPI_H
