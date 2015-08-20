#include "workplace.h"
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QSignalTransition>
#include <QLabel>
#include <QEvent>
#include "transitionsignals.h"

Workplace::Workplace(QObject *parent) : QObject(parent)
{
    mTransitionSignals = new TransitionSignals(this);
    initStateMachine();
}

void Workplace::slotInitSelected()
{
    emit mTransitionSignals->initSelected();
}

void Workplace::slotInitCanceled()
{
    emit mTransitionSignals->initCanceled();
}

void Workplace::slotInitStarted()
{
    emit mTransitionSignals->initStarted();
}

void Workplace::slotInitError()
{
    emit mTransitionSignals->initError();
}

void Workplace::slotInitFinished()
{
    emit mTransitionSignals->initFinished();
}

void Workplace::slotActionSelected()
{
    emit mTransitionSignals->actionSelected();
}

void Workplace::slotActionCanceled()
{
    emit mTransitionSignals->actionCanceled();
}

void Workplace::slotActionConfigured()
{
    emit mTransitionSignals->actionConfigured();
}

void Workplace::slotActionConfigError()
{
    emit mTransitionSignals->actionConfigError();
}

void Workplace::slotActionFinished()
{
    emit mTransitionSignals->actionFinished();
}

void Workplace::slotFatalError()
{
    emit mTransitionSignals->fatalError();
}

void Workplace::slotTabClosed()
{
    emit mTransitionSignals->tabClosed();
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
    QSignalTransition *trTabClosed =
            new QSignalTransition(mTransitionSignals, SIGNAL(tabClosed()));
    trTabClosed->setTargetState(stFinalState);
    stMainState->addTransition(trTabClosed);

    // stValid contains all valid states of SL-workplace
    QState *stValid = new QState(stMainState);
    QState *stNotValid = new QState(stMainState);
    // Transition from any state of stValid to stNotValid state
    // when fatal error occured
    QSignalTransition *trFatalError =
            new QSignalTransition(mTransitionSignals, SIGNAL(fatalError()));
    trFatalError->setTargetState(stNotValid);
    stValid->addTransition(trFatalError);

    // Inner stValid states
    QState *stReady = new QState(stValid);
    QState *stConfiguringInit = new QState(stValid);
    QState *stInitInProgress = new QState(stValid);
    QState *stConfiguringAction = new QState(stValid);
    QState *stActionInProgress = new QState(stValid);

    // Transitions between inner stValid states
    QSignalTransition *trInitSelected =
            new QSignalTransition(mTransitionSignals, SIGNAL(initSelected()));
    trInitSelected->setTargetState(stConfiguringInit);
    stReady->addTransition(trInitSelected);
    QSignalTransition *trActionSelected =
            new QSignalTransition(mTransitionSignals,SIGNAL(actionSelected()));
    trActionSelected->setTargetState(stConfiguringAction);
    stReady->addTransition(trActionSelected);
    QSignalTransition *trInitCanceled
            = new QSignalTransition(mTransitionSignals,SIGNAL(initCanceled()));
    trInitCanceled->setTargetState(stReady);
    stConfiguringInit->addTransition(trInitCanceled);
    QSignalTransition *trInitStarted
            = new QSignalTransition(mTransitionSignals, SIGNAL(initStarted()));
    trInitStarted->setTargetState(stInitInProgress);
    stConfiguringInit->addTransition(trInitStarted);
    QSignalTransition *trInitError
            = new QSignalTransition(mTransitionSignals, SIGNAL(initError()));
    trInitError->setTargetState(stConfiguringInit);
    stInitInProgress->addTransition(trInitError);
    QSignalTransition *trInitFinished
            = new QSignalTransition(mTransitionSignals,SIGNAL(initFinished()));
    trInitFinished->setTargetState(stReady);
    stInitInProgress->addTransition(trInitFinished);
    QSignalTransition *trActionCanceled
            = new QSignalTransition(mTransitionSignals,SIGNAL(actionCanceled()));
    trActionCanceled->setTargetState(stReady);
    stConfiguringAction->addTransition(trActionCanceled);
    QSignalTransition *trActionConfigured
            = new QSignalTransition(mTransitionSignals,SIGNAL(actionConfigured()));
    trActionConfigured->setTargetState(stActionInProgress);
    stConfiguringAction->addTransition(trActionConfigured);
    QSignalTransition *trActionConfigError
            = new QSignalTransition(mTransitionSignals,SIGNAL(actionConfigError()));
    trActionConfigError->setTargetState(stConfiguringAction);
    stActionInProgress->addTransition(trActionConfigError);
    QSignalTransition *trActionFinished
            = new QSignalTransition(mTransitionSignals,SIGNAL(actionFinished()));
    trActionFinished->setTargetState(stReady);
    stActionInProgress->addTransition(trActionFinished);

    // Setting initial states
    stValid->setInitialState(stReady);
    stMainState->setInitialState(stValid);
    mStateMachine->setInitialState(stMainState);

    // Connecting 'entered'-signals from states with signals of class Workplace
    connect(stReady, SIGNAL(entered()), this, SIGNAL(enteredReady()));
    connect(stActionInProgress, SIGNAL(entered()), this, SIGNAL(enteredActionInProgress()));
    connect(stConfiguringAction, SIGNAL(entered()), this, SIGNAL(enteredConfiguringAction()));
    connect(stConfiguringInit, SIGNAL(entered()), this, SIGNAL(enteredConfiguringInit()));
    connect(stFinalState, SIGNAL(entered()), this, SIGNAL(enteredFinalState()));
    connect(stInitInProgress, SIGNAL(entered()), this, SIGNAL(enteredInitInProgress()));
    connect(stNotValid, SIGNAL(entered()), this, SIGNAL(enteredNotValid()));

    mStateMachine->start();
}

