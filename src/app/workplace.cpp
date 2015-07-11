#include "workplace.h"

/*!
 * \brief Public constructor.
 * \param parent Pointer to parent object.
 */
Workplace::Workplace(QObject *parent) : QObject(parent)
{
    initStateMachine();
}

/*!
 * \brief Workplace::slotLinkRepo
 */
void Workplace::slotLinkRepo()
{
    // State "Workplace ready" -> state "Repo selected"
}

/*!
 * \brief Workplace::slotUnlinkFromCurrentRepo
 */
void Workplace::slotUnlinkFromCurrentRepo()
{
    // State "Workplace ready" <- state "Repo selected"
}

/*!
 * \brief Workplace::slotRequestCommandExecution
 */
void Workplace::slotRequestCommandExecution()
{
    // State "Repo selected" substate "Ready" -> State "Repo selected" substate "Configuring Command"
}

/*!
 * \brief Workplace::slotConfigureCommand
 */
void Workplace::slotConfigureCommand()
{
    // State "Repo selected" substate "Configuring Command" -> State "Repo selected" substate "Command InProgress"
}

/*!
 * \brief Workplace::slotReportCommandExecuted
 */
void Workplace::slotReportCommandExecuted()
{
    // State "Repo selected" substate "Command InProgress" -> State "Repo selected" substate "Ready"
}

/*!
 * \brief Workplace::initStateMachine
 */
void Workplace::initStateMachine()
{
    // State machine code goes here...
}

