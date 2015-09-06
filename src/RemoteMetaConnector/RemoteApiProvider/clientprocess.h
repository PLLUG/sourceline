#ifndef CLIENTPROCESS_H
#define CLIENTPROCESS_H

#include <QObject>

class QProcess;

/*!
 * \brief The ClientProcess class is responsible for sl client process control.
 */
class ClientProcess : public QObject
{
    Q_OBJECT
public:
    explicit ClientProcess(QObject *parent = 0);

    void start();

    void setConnectionId(const QString &connectionId);
    void setAllowClientDebugMode(bool isAllowDebug);

signals:
    void ready();

public slots:

private:
    QString clientPath() const;

private:
    QProcess *mProcess;
    bool mIsAllowDebug;
    QString mConnectionId;
};

#endif // CLIENTPROCESS_H
