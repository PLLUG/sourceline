#ifndef CLONECOMMAND_H
#define CLONECOMMAND_H

#include "command.h"

class CloneCommand : public Command
{
    Q_OBJECT
public:
    explicit CloneCommand(QObject *parent = 0);


    virtual QString name() const override;

    virtual void init(Aggregator &api) override;
    virtual void trigger() override;
    virtual void processResult(Aggregator &api) override;

};

#endif // CLONECOMMAND_H
