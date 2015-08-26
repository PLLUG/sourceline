#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

class TestCommand : public Command
{
    Q_OBJECT
public:
    explicit TestCommand(QObject *parent = 0);

    /*!
     * \brief Initializes plugin. Should contain all api calls necessary for command
     * initialization and registration.
     * \param api SL public API aggregator.
     */
    virtual void init(Aggregator &api);

    /*!
     * \brief Should be called when user runs command using associated UI controls.
     * \param api SL public API aggregator.
     */
    virtual void trigger(/*Aggregator &api*/);

    /*!
     * \brief Processes command output and performs appropriate actions.
     * \param api SL public API aggregator.
     */
    virtual void processResult(Aggregator &api);
};

#endif // TESTCOMMAND_H
