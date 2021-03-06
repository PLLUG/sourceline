#ifndef SOURCELINECLIENT_H
#define SOURCELINECLIENT_H

#include <QObject>

class RemoteApiClient;
class TextEditInterface;
class PluginManager;

/*!
 * \brief The SourceLineClient class is responsible for initialization, running and proper shutdown
 * of sl client application.
 */
class SourceLineClient : public QObject
{
    Q_OBJECT
public:
    explicit SourceLineClient(const QString &connectionId, QObject *parent = 0);
    virtual ~SourceLineClient();

    void start();
    void showDebugWindow();

private slots:
    void test();
    void initPlugins();

private:
    QString mConnectionId;

    RemoteApiClient *mRemoteClient;
    TextEditInterface *mInterface;
    QWidget *mDebugWindowInstance;
    PluginManager *mPluginManager;
};

#endif // SOURCELINECLIENT_H
