#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QString>
#include <QHash>

class CommandInterface;
class PluginAPI;

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(QObject *parent = 0);

    CommandInterface* command(QString pCommandID);
signals:
    void invokeCommand(QString pCommandID, QByteArray pSignature);
public slots:
    void slotCommandRegistered(QString pCommandID);
    void slotInvokeCommand(QString pCommandID);
    void slotInvoke(QString pCommandID, QByteArray pSignature);

private:
    QHash<QString, CommandInterface*> mCommandsAPI;

};

#endif // COMMANDMANAGER_H
