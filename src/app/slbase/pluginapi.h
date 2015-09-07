#ifndef PLUGINAPI_H
#define PLUGINAPI_H

#include <QObject>
#include <QHash>
#include <QString>

class TestCommand;
class InvocationBased;
class Command;

class PluginAPI : public QObject
{
    Q_OBJECT
public:
    explicit PluginAPI(QObject *parent = 0);

signals:
    void newCommandRegistered(QString pID);

public slots:
    void slotRegisterCommand(Command *pCommand);
    void slotInvokeCommand(QString pCommandID, QByteArray pSignature);

private:
    QHash<QString, InvocationBased*> mRegisteredCommands;
};

#endif // PLUGINAPI_H
