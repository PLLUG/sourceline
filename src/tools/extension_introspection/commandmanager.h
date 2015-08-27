#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QString>
#include <QList>

class PublicCommandAPI;
class PluginAPI;

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QObject *parent = 0);

signals:
    void invokeCommand(QString pCommandID, QByteArray pSignature);
public slots:
    void slotCommandRegistered(QString pCommandID);
    void slotInvokeCommand();
    void slotInvoke(QString pCommandID, QByteArray pSignature);

private:
    PublicCommandAPI* mCommandsAPI;

};

#endif // COMMANDMANAGER_H
