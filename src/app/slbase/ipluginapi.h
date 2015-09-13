#ifndef IPLUGINAPI
#define IPLUGINAPI

#include <QObject>
#include "defs.h"

class Command;

class IPLuginAPI : public QObject
{
    Q_OBJECT
public:
    IPLuginAPI(QObject *parent = nullptr) : QObject(parent) { }
    virtual ~IPLuginAPI() { }

    virtual void registerCommand(const QMetaObject &metaObj, Commands::CommandKind kind) = 0;

signals:
    void newCommandRegistered(QString pID);
};

#endif // IPLUGINAPI

