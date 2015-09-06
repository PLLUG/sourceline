#include "sourcelineclient.h"

#include <QTimer>
#include "remoteapiclient.h"
#include "texteditinterface.h"

#ifdef DEBUG
    // Include debug window only in Debug mode.
    #include "clientdebugwindow.h"
#endif

/*!
 * \brief Public constructor.
 * \param connectionId Client connection id.
 * \param parent Pointer to parent object.
 */
SourceLineClient::SourceLineClient(const QString &connectionId, QObject *parent) :
    QObject(parent)
  , mConnectionId{connectionId}
  , mRemoteClient{new RemoteApiClient(this)}
  , mDebugWindowInstance{nullptr}
{
}

SourceLineClient::~SourceLineClient()
{
    if (mDebugWindowInstance)
    {
        delete mDebugWindowInstance;
    }
}

/*!
 * \brief Begin process of client initialization and starting.
 */
void SourceLineClient::start()
{
    mRemoteClient->connectToProvider(mConnectionId);
    mInterface = new TextEditInterface();
    connect(mInterface, &TextEditInterface::invoked, mRemoteClient, &RemoteApiClient::slotInvoke, Qt::UniqueConnection);
    QTimer::singleShot(1000, this, SLOT(test()));
}

/*!
 * \brief Shows client window for debugging purposes. Does nothing in release mode.
 */
void SourceLineClient::showDebugWindow()
{
#ifdef DEBUG
    if (!mDebugWindowInstance)
    {
        qDebug("Showing debug window...");
        mDebugWindowInstance = new ClientDebugWindow();
        mDebugWindowInstance->show();
    }
#endif
}

void SourceLineClient::test()
{
    mInterface->setText("Hello, SL!");
}

