#ifndef COMMANDPROCESSMEDIATOR_H
#define COMMANDPROCESSMEDIATOR_H

#include <QObject>
#include "commandprocess.h"

class CommandProcessMediator : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcessMediator(QObject *parent = 0);

signals:
    void execute(QString);
    void commandMapped(QString commandId);
    void processStandardOutput(QByteArray out);
    void processErrorOutput(QByteArray out);
    void processStarted();
    void processFinished();

public slots:
    void processConsoleInput(QString input);

    void registerCommand(QString commandId, QString inputPattern);

private:
     CommandProcess *mProcess;
};

#endif // COMMANDPROCESSMEDIATOR_H
