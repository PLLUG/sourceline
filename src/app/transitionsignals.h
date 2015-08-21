#ifndef TRANSITIONSIGNALS
#define TRANSITIONSIGNALS

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

/*!
 * \brief The TransitionSignals class provides signals.
 *
 * These signals are emitted in order to make transitions between
 * states of state machine.
 */
class TransitionSignals : public QObject
{
    Q_OBJECT
public:
    explicit TransitionSignals(QObject *parent = 0) : QObject(parent)
    {
    }

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
};

#endif // TRANSITIONSIGNALS

