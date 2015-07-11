#include "workplace.h"
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QSignalTransition>
#include <QLabel>

Workplace::Workplace(QObject *parent) :
    QObject(parent),
    mWorkplaceInitialized(false)
{
    initStateMachine();
}

void Workplace::slotInitSelected()
{
    emit initSelected();
}

void Workplace::slotInitCanceled()
{
    emit initCanceled();
}

void Workplace::slotInitStarted()
{
    emit initStarted();
}

void Workplace::slotInitError()
{
    emit initError();
}

void Workplace::slotInitFinished()
{
    emit initFinished();
}

void Workplace::slotActionSelected()
{
    emit actionSelected();
}

void Workplace::slotActionCanceled()
{
    emit actionCanceled();
}

void Workplace::slotActionConfigured()
{
    emit actionConfigured();
}

void Workplace::slotActionConfigError()
{
    emit actionConfigError();
}

void Workplace::slotActionFinished()
{
    emit actionFinished();
}

void Workplace::slotFatalError()
{
    emit fatalError();
}

void Workplace::slotTabClosed()
{
    emit tabClosed();
}

void Workplace::initStateMachine()
{
    // State machine code goes here...
    mStateMachine = new QStateMachine(this);

    // stMainState contains stValid and stNotValid states
    QState *stMainState = new QState(mStateMachine);
    QFinalState *stFinalState = new QFinalState(mStateMachine);
    // Transition from any state, that stMainState contains,
    // to stFinalState, when closing the tab
    stMainState->addTransition(this, SIGNAL(tabClosed()), stFinalState);

    // stValid contains all valid states of SL-workplace
    QState *stValid = new QState(stMainState);
    QState *stNotValid = new QState(stMainState);
    // Transition from any state of stValid to stNotValid state
    // when fatal error occured
    stValid->addTransition(this, SIGNAL(fatalError()), stNotValid);

    // Inner stValid states
    QState *stReady = new QState(stValid);
    QState *stConfiguringInit = new QState(stValid);
    QState *stInitInProgress = new QState(stValid);
    QState *stConfiguringAction = new QState(stValid);
    QState *stActionInProgress = new QState(stValid);

    // Transitions between inner stValid states
    stReady->addTransition(this, SIGNAL(initSelected()), stConfiguringInit);
    stReady->addTransition(this, SIGNAL(actionSelected()), stConfiguringAction);
    stConfiguringInit->addTransition(this, SIGNAL(initCanceled()), stReady);
    stConfiguringInit->addTransition(this, SIGNAL(initStarted()),
                                     stInitInProgress);
    stInitInProgress->addTransition(this, SIGNAL(initError()),
                                    stConfiguringInit);
    stInitInProgress->addTransition(this, SIGNAL(initFinished()), stReady);
    stConfiguringAction->addTransition(this, SIGNAL(actionCanceled()), stReady);
    stConfiguringAction->addTransition(this, SIGNAL(actionConfigured()),
                                       stActionInProgress);
    stActionInProgress->addTransition(this, SIGNAL(actionConfigError()),
                                      stConfiguringAction);
    stActionInProgress->addTransition(this, SIGNAL(actionFinished()), stReady);

    // Setting initial states
    stValid->setInitialState(stReady);
    stMainState->setInitialState(stValid);
    mStateMachine->setInitialState(stMainState);

    mStateMachine->start();
}

