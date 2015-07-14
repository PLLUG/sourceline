#ifndef TRANSITIONSIGNALS
#define TRANSITIONSIGNALS

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
    explicit TransitionSignals(QObject *parent) : QObject(parent)
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

