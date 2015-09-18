#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QString>
#include <QHash>

class PublicCommandAPI;
class PluginAPI;

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QObject *parent = 0);

    PublicCommandAPI* command(QString pCommandID);
signals:
    void invokeCommand(QString pCommandID, QByteArray pSignature);
public slots:
    void slotCommandRegistered(QString pCommandID);
    void slotInvokeCommand(QString pCommandID);
    void slotInvoke(QString pCommandID, QByteArray pSignature);

private:
    QHash<QString, PublicCommandAPI*> mCommandsAPI;

};

#endif // COMMANDMANAGER_H
