#ifndef COMMAND_H
#define COMMAND_H

/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014, 2015  by                                                ***
***            Alex Chmykhalo (alexchmykhalo@users.sourceforge.net)          ***
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

#include <QIcon>
#include "defs.h"
#include "extensions_global.h"

class Aggregator;

/*!
 * \brief The abstract Command class implements command that could be executed by vcs or command
 *  interpreter in SL process execution environment.
 */
class EXTENSIONSSHARED_EXPORT Command : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief The CommandFlag enum describes specific command properties.
     */
    enum CommandFlag
    {
        NoFlags = 0x0000
    };
    Q_DECLARE_FLAGS(CommandFlags, CommandFlag)

    explicit Command(QObject *parent = 0);

    /*!
     * \brief Returns visible to user name that describes command.
     * \return String with command name.
     */
    virtual QString name() const = 0;

    /*!
     * \brief Returns visible to user icon that describes command.
     * \return Command icon.
     */
    QIcon icon() const;

    /*!
     * \brief Returns flags that describes command type and behavior for application. Aplication takes
     *  this flags into accoutn when command will be supplied from plugin.
     * \return CommandFlags class.
     */
    virtual CommandFlags flags() const;

//    virtual QString commandString() const = 0;
//    virtual QStringList parametersList() const = 0;
//    /*!
//     * \brief commandKind Return flags that describers type of command
//     * \return this flag
//     */
//    virtual Commands::CommandKind commandKind() const  = 0;

//    /*!
//     * \brief Returns string that equivalent to command in command line to execute current Command
//     *  instance.
//     * \return String with command and parameters.
//     */
//    QString toString() const;

    /*!
     * \brief Initializes plugin. Should contain all api calls necessary for command
     * initialization and registration.
     * \param api SL public API aggregator.
     */
    virtual void init(Aggregator &api) = 0;

    /*!
     * \brief Should be called when user runs command using associated UI controls.
     * \param api SL public API aggregator.
     */
    virtual void trigger(Aggregator &api) = 0;

    /*!
     * \brief Processes command output and performs appropriate actions.
     * \param api SL public API aggregator.
     */
    virtual void processResult(Aggregator &api) = 0;

protected:
    /*!
     * \brief Sets visible to user icon that describes command.
     * \param Command icon.
     */
    void setIcon(const QIcon &pIcon);

private:
    QIcon mIcon;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Command::CommandFlags)

#endif // COMMAND_H
