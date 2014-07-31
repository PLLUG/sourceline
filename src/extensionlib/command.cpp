#include "command.h"

#include <QStringList>

const QChar ARGUMENT_SEPARATOR(' ');

Command::Command(QObject *parent) :
    QObject(parent)
{
}

QString Command::name() const
{
    return mName;
}

QIcon Command::icon() const
{
    return mIcon;
}

Command::CommandFlags Command::flags() const
{
    return NoFlags;
}

QString Command::toString() const
{
    return QString("%1 %2")
        .arg(commandString())
        .arg(parametersList().join(ARGUMENT_SEPARATOR));
}

void Command::setName(const QString &pName)
{
    mName = pName;
}

void Command::setIcon(const QIcon &pIcon)
{
    mIcon = pIcon;
}
