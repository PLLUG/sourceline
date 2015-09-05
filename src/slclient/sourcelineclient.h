#ifndef SOURCELINECLIENT_H
#define SOURCELINECLIENT_H

#include <QObject>

/*!
 * \brief The SourceLineClient class is responsible for initialization, running and proper shutdown
 * of sl client application.
 */
class SourceLineClient : public QObject
{
    Q_OBJECT
public:
    explicit SourceLineClient(const QString &connectionId, QObject *parent = 0);

    void start();

private:
    QString mConnectionId;
};

#endif // SOURCELINECLIENT_H
