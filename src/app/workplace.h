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
class QLabel;
class QEvent;

/*!
 * \brief The Workplace class is responsinble for handling state
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
     * \brief Emitted when initialization was selected.
     */
    void initSelected();
    /*!
     * \brief Emitted when initialization was canceled.
     */
    void initCanceled();
    /*!
     * \brief Emitted when initialization started.
     */
    void initStarted();
    /*!
     * \brief Emitted when some errors occured, while initializing.
     */
    void initError();
    /*!
     * \brief Emitted when initialization finished
     */
    void initFinished();
    /*!
     * \brief Emitted when action was selected.
     */
    void actionSelected();
    /*!
     * \brief Emitted when action was canceled.
     */
    void actionCanceled();
    /*!
     * \brief Emitted when action was configured.
     */
    void actionConfigured();
    /*!
     * \brief Emitted when some errors occured during the action.
     */
    void actionConfigError();
    /*!
     * \brief Emitted when action was finished.
     */
    void actionFinished();
    /*!
     * \brief Emitted when fatal error occured in any states of workplace.
     */
    void fatalError();
    /*!
     * \brief Emitted when tab was closed.
     */
    void tabClosed();

public slots:
    /*!
     * \brief Make transition from state "Ready"
     *  to "Configuring Initialization" of workplace.
     */
    void slotInitSelected();
    /*!
     * \brief Make transition from state "Configuring Initialization"
     *  to "Ready" of workplace.
     */
    void slotInitCanceled();
    /*!
     * \brief Make transition from state "Configuring Initialization"
     *  to "Initialization in progress" of workplace.
     */
    void slotInitStarted();
    /*!
     * \brief Make transition from state "Initialization in progress"
     *  to "Configuring Initialization" of workplace.
     */
    void slotInitError();
    /*!
     * \brief Make transition from state "Initialization in progress"
     *  to "Ready" of workplace.
     */
    void slotInitFinished();
    /*!
     * \brief Make transition from state "Ready"
     *  to "Configuring Action" of workplace.
     */
    void slotActionSelected();
    /*!
     * \brief Make transition from state "Configuring Action"
     *  to "Ready" of workplace.
     */
    void slotActionCanceled();
    /*!
     * \brief Make transition from state "Configuring Action"
     *  to "Action In Progress" of workplace.
     */
    void slotActionConfigured();
    /*!
     * \brief Make transition from state "Action In Progress"
     *  to "Configuring Action" of workplace.
     */
    void slotActionConfigError();
    /*!
     * \brief Make transition from state "Action In Progress"
     *  to "Ready" of workplace.
     */
    void slotActionFinished();
    /*!
     * \brief Make transition from any state to state "Not valid" of workplace.
     */
    void slotFatalError();
    /*!
     * \brief Make transition from any state to final state of workplace.
     */
    void slotTabClosed();

private:
    /*!
     * \brief Initialization of state machine with all states and transitions.
     */
    void initStateMachine();

private:
    /*!
     * \brief The SLEventType enum represents event types.
     *
     * They will be sended to state machine, when ones slot will be invoked.
     */
    enum SLEventType{

        /// Initialization selected event type
        EvInitSelected = QEvent::User + 1,          // 1
        /// Initialization canceled event type
        EvInitCanceled,                             // 2
        /// Initialization started event type
        EvInitStarted,                              // 3
        /// Initialization error event type
        EvInitError,                                // 4
        /// Initialization finished event type
        EvInitFinished,                             // 5
        /// Action selected event type
        EvActionSelected,                           // 6
        /// Action canceled event type
        EvActionCanceled,                           // 7
        /// Action configured event type
        EvActionConfigured,                         // 8
        /// Action configuration error event type
        EvActionConfigError,                        // 9
        /// Action finished event type
        EvActionFinished,                           // 10
        /// Fatal error event type
        EvFatalError,                               // 11
        /// Tab closed event type
        EvTabClosed                                 // 12
    };

    QStateMachine *mStateMachine; /*!< State machine for single workplace */
    bool mWorkplaceInitialized;
};

#endif // WORKPLACE_H
