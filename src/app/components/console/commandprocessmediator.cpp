#include "commandprocessmediator.h"

#include <QProcess>
#include <QVariant>

CommandProcessMediator::CommandProcessMediator(QObject *parent) : QObject(parent)
{
    mProcess = new CommandProcess(this);
    // !!hardcode!! , dont work on linux , set for "shell" property "sh"
    mProcess->setProperty("shell","C:\\Windows\\System32\\cmd");
    mProcess->setProperty("shellParam",QStringList()<< "/k");
    mProcess->start();

    connect(this, SIGNAL(execute(QString)), mProcess, SLOT(execute(QString)));
    connect(mProcess, SIGNAL(started()), this, SIGNAL(processStarted()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished()), this, SIGNAL(processFinished()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(standardOutput(QByteArray)), this, SIGNAL(processStandardOutput(QByteArray)), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(errorOutput(QByteArray)), this, SIGNAL(processErrorOutput(QByteArray)), Qt::UniqueConnection);
}

void CommandProcessMediator::processConsoleInput(QString input)
{
    emit execute(input);
}

void CommandProcessMediator::registerCommand(QString commandId, QString inputPattern)
{

}

