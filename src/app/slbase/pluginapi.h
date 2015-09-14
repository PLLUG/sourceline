#ifndef PLUGINAPI_H
#define PLUGINAPI_H

#include "ipluginapi.h"

#include <QObject>
#include <QHash>
#include <QString>

class TestCommand;
class InvocationBased;
class Command;

class PluginAPI : public IPLuginAPI
{
    Q_OBJECT
public:
    explicit PluginAPI(QObject *parent = 0);

    virtual void registerCommand(const QMetaObject &metaObj, Commands::CommandKind kind) final;

    QList<Command *> commands(Commands::CommandKind kind = Commands::UknownKind);

public slots:
    void slotInvokeCommand(QString pCommandID, QByteArray pSignature);

private:
    QMultiHash<int, const QMetaObject *> mCommandMetaObjectByKind;
    QMultiHash<int, Command *> mCommandByKind;

    QHash<QString, InvocationBased*> mRegisteredCommands;
};

#endif // PLUGINAPI_H
