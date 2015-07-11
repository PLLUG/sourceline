#include "workplace.h"

/*!
 * \brief Public constructor.
 * \param parent Pointer to parent object.
 */
Workplace::Workplace(QObject *parent) : QObject(parent)
{
    initStateMachine();
}

void Workplace::slotInitSelected()
{

}

void Workplace::slotInitCanceled()
{

}

void Workplace::slotInitStarted()
{

}

void Workplace::slotInitError()
{

}

void Workplace::slotActionSelected()
{

}

void Workplace::slotActionCanceled()
{

}

void Workplace::slotActionConfigured()
{

}

void Workplace::slotActionConfigError()
{

}

void Workplace::slotActionFinished()
{

}

void Workplace::slotFatalError()
{

}

void Workplace::slotCloseTab()
{

}

void Workplace::initStateMachine()
{
    // State machine code goes here...
}

