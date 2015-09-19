#ifndef PLUGINAPIINTERFACE
#define PLUGINAPIINTERFACE

#include "ipluginapi.h"

#include <QObject>
#include <QHash>
#include <QString>


class TestCommand;
class InvocationBased;
class Command;

class PluginApiInterface : public IPLuginAPI
{
public:
    PluginApiInterface(QObject *parent = 0) : IPLuginAPI(parent) {}
    ~PluginApiInterface() {}

    virtual void registerCommand(const QMetaObject &metaObj, Commands::CommandKind kind) final;

    QList<Command *> commands(Commands::CommandKind kind = Commands::UknownKind);

public slots:
    void slotInvokeCommand(QString pCommandID, QByteArray pSignature);

private:
    QMultiHash<int, const QMetaObject *> mCommandMetaObjectByKind;
    QMultiHash<int, Command *> mCommandByKind;

    QHash<QString, InvocationBased*> mRegisteredCommands;
};

#endif // PLUGINAPIINTERFACE

