#ifndef COMAMNDINTERFACE_H
#define COMAMNDINTERFACE_H

#include "icommand.h"

class CommandInterface : public ICommand
{
    Q_OBJECT
public:
    CommandInterface(QObject *parent = 0) : ICommand (parent) {}
    virtual ~CommandInterface() {}

signals:
    void invokeCommand(QByteArray pSignature, QVariant, QVariant, QVariant, QVariant, QVariant);

public slots:
    void trigger() final
    {
        emit invokeCommand("trigger()", QVariant(), QVariant(), QVariant(), QVariant(), QVariant());
    }
};

#endif // COMAMNDINTERFACE_H

