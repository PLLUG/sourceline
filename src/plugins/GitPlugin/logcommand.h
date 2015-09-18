#ifndef LOGCOMMAND_H
#define LOGCOMMAND_H

#include "command.h"
class QProcess;

class LogCommand : public Command
{
    Q_OBJECT
public:
    explicit LogCommand(QObject *parent = 0);

    virtual QString name() const override;

public slots:
    virtual void init(Aggregator &api) override;
    virtual void trigger() override;
    virtual void processResult(Aggregator &api) override;

private:
    QProcess *mProcess;//just a test
};

#endif // LOGCOMMAND_H
