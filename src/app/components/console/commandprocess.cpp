#include "commandprocess.h"

#include <QProcess>

CommandProcess::CommandProcess(QObject *parent)
    : QObject(parent),
      mProcess(new QProcess(this))
{
    connect(mProcess, SIGNAL(started()), this, SIGNAL(started()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished(int)), this, SIGNAL(finished()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(readStandardError()), Qt::UniqueConnection);
}

void CommandProcess::execute(QString command, QStringList parameters)
{
    mProcess->start(command, parameters);
}

void CommandProcess::readStandardOutput()
{

}

void CommandProcess::readStandardError()
{

}

