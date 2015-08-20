#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

class CloneCommand : public Command
{
    Q_OBJECT

private:
    QString commandName;

public:
    /*!
     * \brief Set up name and icon for command
     * \param parent
     */
    CloneCommand(QObject *parent = nullptr);

    void init(Aggregator &api);

    void trigger(Aggregator &api);

    void processResult(Aggregator &api);

    /*!
     * \brief Return command name
     * \return
     */
    QString name() const
    {
        return commandName;
    }
};

#endif // TESTCOMMAND_H
