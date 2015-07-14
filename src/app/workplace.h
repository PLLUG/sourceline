#ifndef WORKPLACE_H
#define WORKPLACE_H

/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Nazarii Plebanskii (nazar796@gmail.com)                       ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#include <QObject>

class QStateMachine;
class TransitionSignals;

/*!
 * \brief The Workplace class is responsible for handling state
 *  of certain SL user workplace. It also contains various related information.
 */
class Workplace : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Public constructor.
     * \param parent Pointer to parent object.
     */
    explicit Workplace(QObject *parent = 0);

signals:
    /*!
     * \brief Emitted when entered in state "Ready"
     */
    void enteredReady();
    /*!
     * \brief Emitted when entered in state "Configuring Initialization"
     */
    void enteredConfiguringInit();
    /*!
     * \brief Emitted when entered in state "Initialization In Progress"
     */
    void enteredInitInProgress();
    /*!
     * \brief Emitted when entered in state "Configuring Action"
     */
    void enteredConfiguringAction();
    /*!
     * \brief Emitted when entered in state "Action In Progress"
     */
    void enteredActionInProgress();
    /*!
     * \brief Emitted when entered in state "Not Valid"
     */
    void enteredNotValid();
    /*!
     * \brief Emitted when entered in state "Final State"
     */
    void enteredFinalState();

public slots:
    /*!
     * \brief Makes transition from state "Ready"
     *  to "Configuring Initialization" of workplace.
     */
    void slotInitSelected();
    /*!
     * \brief Makes transition from state "Configuring Initialization"
     *  to "Ready" of workplace.
     */
    void slotInitCanceled();
    /*!
     * \brief Makes transition from state "Configuring Initialization"
     *  to "Initialization in progress" of workplace.
     */
    void slotInitStarted();
    /*!
     * \brief Makes transition from state "Initialization in progress"
     *  to "Configuring Initialization" of workplace.
     */
    void slotInitError();
    /*!
     * \brief Makes transition from state "Initialization in progress"
     *  to "Ready" of workplace.
     */
    void slotInitFinished();
    /*!
     * \brief Makes transition from state "Ready"
     *  to "Configuring Action" of workplace.
     */
    void slotActionSelected();
    /*!
     * \brief Makes transition from state "Configuring Action"
     *  to "Ready" of workplace.
     */
    void slotActionCanceled();
    /*!
     * \brief Makes transition from state "Configuring Action"
     *  to "Action In Progress" of workplace.
     */
    void slotActionConfigured();
    /*!
     * \brief Makes transition from state "Action In Progress"
     *  to "Configuring Action" of workplace.
     */
    void slotActionConfigError();
    /*!
     * \brief Makes transition from state "Action In Progress"
     *  to "Ready" of workplace.
     */
    void slotActionFinished();
    /*!
     * \brief Makes transition from any state to state "Not valid" of workplace.
     */
    void slotFatalError();
    /*!
     * \brief Makes transition from any state to final state of workplace.
     */
    void slotTabClosed();

private:
    /*!
     * \brief Initialization of state machine with all states and transitions.
     */
    void initStateMachine();

private:

    QStateMachine *mStateMachine; /*!< State machine for single workplace */
    TransitionSignals *mTransitionSignals;
};

#endif // WORKPLACE_H
