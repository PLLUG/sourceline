#include "clientprocess.h"

#include <QProcess>
#include <QApplication>

#include "remoteapiprovider.h"

static const QString SL_CLIENT_EXECUTABLE_NAME("slclient");
#ifdef Q_OS_WIN
static const QString SL_CLIENT_EXECUTABLE_EXTENSION(".exe");
#else
static const QString SL_CLIENT_EXECUTABLE_EXTENSION("");
#endif

static const QString OPTION_CONNECTION_ID("--id");
static const QString OPTION_DEBUG("--debug");

ClientProcess::ClientProcess(RemoteApiProvider &remoteApiProvider, QObject *parent) :
    QObject(parent)
  , mProcess{new QProcess(this)}
  , mIsAllowDebug{false}
  , mRemoteApiProvider{remoteApiProvider}
{
    connect(mProcess, &QProcess::started, this, &ClientProcess::ready, Qt::UniqueConnection);
}

void ClientProcess::start()
{
    QStringList args;

    if (!mConnectionId.isEmpty())
    {
        args << OPTION_CONNECTION_ID;
        args << mConnectionId;
    }
    else
    {
        qDebug("Could not start client process - id is not set.");
    }

    if (mIsAllowDebug)
    {
        args << OPTION_DEBUG;
    }

    mRemoteApiProvider.listen(mConnectionId);

    Q_CHECK_PTR(mProcess);
    mProcess->start(clientPath(), args);
}

void ClientProcess::setConnectionId(const QString &connectionId)
{
    mConnectionId = connectionId;
}

void ClientProcess::setAllowClientDebugMode(bool isAllowDebug)
{
    mIsAllowDebug = isAllowDebug;
}

QString ClientProcess::clientPath() const
{
    // SL client should be located in the same directory as SL executable
    QString rSlClientPath = QString("%1/%2").arg(QApplication::applicationDirPath(), SL_CLIENT_EXECUTABLE_NAME);

    if (!SL_CLIENT_EXECUTABLE_EXTENSION.isEmpty())
    {
        rSlClientPath.append(SL_CLIENT_EXECUTABLE_EXTENSION);
    }

    return rSlClientPath;
}

