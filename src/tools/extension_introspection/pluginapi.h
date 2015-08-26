#ifndef PLUGINAPI_H
#define PLUGINAPI_H

#include <QObject>
#include <QHash>
#include <QString>

#include "testcommand.h"
class InvocationBased;

class PluginAPI : public QObject
{
    Q_OBJECT
public:
    explicit PluginAPI(QObject *parent = 0);

signals:
    void newCommandRegistered(QString pID);

public slots:
    void slotRegisterCommand(TestCommand *pCommand);
    void slotInvokeCommand(QString pCommandID, QByteArray pSignature);

private:
    QHash<QString, InvocationBased*> mRegisteredCommands;
};

#endif // PLUGINAPI_H
