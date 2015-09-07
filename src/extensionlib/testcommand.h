#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

class TestCommand : public Command
{
    Q_OBJECT

public:
    TestCommand(QObject *parent = nullptr);
    //TestCommand(QString str, QString pr1 = 0, QString pr2 = 0, QObject *parent = nullptr);
    QString commandString() const;
    QStringList parametersList() const;
    QString name() const
    {
        return commandStr;
    }
    Commands::CommandKind commandKind() const
    {
        return Commands::UknownCommand;
    }
private:
    QString commandStr;
    QStringList paramList;
};

#endif // TESTCOMMAND_H
