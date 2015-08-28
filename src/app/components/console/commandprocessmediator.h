#ifndef COMMANDPROCESSMEDIATOR_H
#define COMMANDPROCESSMEDIATOR_H

#include <QObject>

class CommandProcessMediator : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcessMediator(QObject *parent = 0);

signals:
    void execute(QString);
    void commandMapped(QString commandId);

public slots:
    void processConsoleInput(QString input);

    void registerCommand(QString commandId, QString inputPattern);
};

#endif // COMMANDPROCESSMEDIATOR_H
