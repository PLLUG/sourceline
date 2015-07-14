#include "workplace.h"
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QEventTransition>
#include <QLabel>
#include <QEvent>
#include <QCoreApplication>

Workplace::Workplace(QObject *parent) : QObject(parent)
{
    initStateMachine();
}

void Workplace::slotInitSelected()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvInitSelected)));
}

void Workplace::slotInitCanceled()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvInitCanceled)));
}

void Workplace::slotInitStarted()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvInitStarted)));
}

void Workplace::slotInitError()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvInitError)));
}

void Workplace::slotInitFinished()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvInitFinished)));
}

void Workplace::slotActionSelected()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvActionSelected)));
}

void Workplace::slotActionCanceled()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvActionCanceled)));
}

void Workplace::slotActionConfigured()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvActionConfigured)));
}

void Workplace::slotActionConfigError()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvActionConfigError)));
}

void Workplace::slotActionFinished()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvActionFinished)));
}

void Workplace::slotFatalError()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvFatalError)));
}

void Workplace::slotTabClosed()
{
    QCoreApplication::sendEvent(this, new QEvent(QEvent::Type(EvTabClosed)));
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
    QEventTransition *trTabClosed = new QEventTransition(this, QEvent::Type(EvTabClosed));
    trTabClosed->setTargetState(stFinalState);
    stMainState->addTransition(trTabClosed);

    // stValid contains all valid states of SL-workplace
    QState *stValid = new QState(stMainState);
    QState *stNotValid = new QState(stMainState);
    // Transition from any state of stValid to stNotValid state
    // when fatal error occured
    QEventTransition *trFatalError = new QEventTransition(this, QEvent::Type(EvFatalError));
    trFatalError->setTargetState(stNotValid);
    stValid->addTransition(trFatalError);

    // Inner stValid states
    QState *stReady = new QState(stValid);
    QState *stConfiguringInit = new QState(stValid);
    QState *stInitInProgress = new QState(stValid);
    QState *stConfiguringAction = new QState(stValid);
    QState *stActionInProgress = new QState(stValid);

    // Transitions between inner stValid states
    QEventTransition *trInitSelected =
            new QEventTransition(this, QEvent::Type(EvInitSelected));
    trInitSelected->setTargetState(stConfiguringInit);
    stReady->addTransition(trInitSelected);
    QEventTransition *trActionSelected =
            new QEventTransition(this, QEvent::Type(EvActionSelected));
    trActionSelected->setTargetState(stConfiguringAction);
    stReady->addTransition(trActionSelected);
    QEventTransition *trInitCanceled
            = new QEventTransition(this, QEvent::Type(EvInitCanceled));
    trInitCanceled->setTargetState(stReady);
    stConfiguringInit->addTransition(trInitCanceled);
    QEventTransition *trInitStarted
            = new QEventTransition(this, QEvent::Type(EvInitStarted));
    trInitStarted->setTargetState(stInitInProgress);
    stConfiguringInit->addTransition(trInitStarted);
    QEventTransition *trInitError
            = new QEventTransition(this, QEvent::Type(EvInitError));
    trInitError->setTargetState(stConfiguringInit);
    stInitInProgress->addTransition(trInitError);
    QEventTransition *trInitFinished
            = new QEventTransition(this, QEvent::Type(EvInitFinished));
    trInitFinished->setTargetState(stReady);
    stInitInProgress->addTransition(trInitFinished);
    QEventTransition *trActionCanceled
            = new QEventTransition(this, QEvent::Type(EvActionCanceled));
    trActionCanceled->setTargetState(stReady);
    stConfiguringAction->addTransition(trActionCanceled);
    QEventTransition *trActionConfigured
            = new QEventTransition(this, QEvent::Type(EvActionConfigured));
    trActionConfigured->setTargetState(stActionInProgress);
    stConfiguringAction->addTransition(trActionConfigured);
    QEventTransition *trActionConfigError
            = new QEventTransition(this, QEvent::Type(EvActionConfigError));
    trActionConfigError->setTargetState(stConfiguringAction);
    stActionInProgress->addTransition(trActionConfigError);
    QEventTransition *trActionFinished
            = new QEventTransition(this, QEvent::Type(EvActionFinished));
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

