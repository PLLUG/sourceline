#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

#include <QIcon>

#include "extensions_global.h"

/*!
 * \brief The abstract Command class implements command that could be executed by vcs or command
 *  interpreter in SL process execution environment.
 */
class EXTENSIONSSHARED_EXPORT Command : public QObject
{
    Q_OBJECT
public:
    enum CommandFlags {
        NoFlags = 0x0000
    };

    explicit Command(QObject *parent = 0);

    /*!
     * \brief Returns visible to user name that describes command.
     * \return String with command name.
     */
    QString name() const;

    /*!
     * \brief Returns visible to user icon that describes command.
     * \return Command icon.
     */
    QIcon icon() const;

    /*!
     * \brief Returns flags that describes command type and behavior for application. Aplication takes
     *  this flags into accoutn when command will be supplied from plugin.
     * \return CommandFlags enum.
     */
    virtual CommandFlags flags() const;

    virtual QString commandString() const = 0;
    virtual QStringList parametersList() const = 0;

    QString toString() const;

signals:

public slots:

protected:
    /*!
     * \brief Sets visible to user name that describes command.
     * \param pName String with command name.
     */
    void setName(const QString &pName);

    /*!
     * \brief Sets visible to user icon that describes command.
     * \param Command icon.
     */
    void setIcon(const QIcon &pIcon);

private:
    QString mName;
    QIcon mIcon;
};

#endif // COMMAND_H
