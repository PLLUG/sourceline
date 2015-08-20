#include "testcommand.h"

TestCommand::TestCommand(QString str, QString pr1, QString pr2, QObject *parent) : Command(parent)
{
    commandStr = str;
    paramList.push_back(pr1);
    paramList.push_back(pr2);
}

/*TestCommand::TestCommand(QObject *parent) : Command(parent)
{

}*/

QString TestCommand::commandString() const
{
    return commandStr;
}

QStringList TestCommand::parametersList() const
{
    return paramList;
}
