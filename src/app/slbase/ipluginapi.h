#ifndef IPLUGINAPI
#define IPLUGINAPI

#include <QObject>

class Command;

class IPLuginAPI : public QObject
{
    Q_OBJECT
public:
    IPLuginAPI(QObject *parent = nullptr) : QObject(parent) { }
    virtual ~IPLuginAPI() { }

    virtual void registerCommand(Command *command) = 0;

signals:
    void newCommandRegistered(QString pID);
};

#endif // IPLUGINAPI

