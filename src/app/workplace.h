#ifndef WORKPLACE_H
#define WORKPLACE_H

#include <QObject>

/*!
 * \brief The Workplace class is responsinble for handling state of certain SL user worplace.
 * It also contains various related information.
 */
class Workplace : public QObject
{
    Q_OBJECT
public:
    explicit Workplace(QObject *parent = 0);

signals:
    /*!
     * \brief Emmitted when workplace is fully initialised and ready for work.
     */
    void workplaceInitializsed();

    /*!
     * \brief Emmited when command configuration started with ActionManager.
     */
    void commandConfigurationStarted();

    /*!
     * \brief Emmited when command is in progress.
     */
    void commandInProgress();

    /*!
     * \brief Emmited when command executed in workplace is finished.
     */
    void commandFinished();

public slots:
    void slotLinkRepo();
    void slotUnlinkFromCurrentRepo();

    void slotRequestCommandExecution();
    void slotConfigureCommand();
    void slotReportCommandExecuted();

private:
    void initStateMachine();
};

#endif // WORKPLACE_H
