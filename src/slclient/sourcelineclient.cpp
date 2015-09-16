#include "sourcelineclient.h"

#include <QTimer>

#include "remoteapiclient.h"
#include "texteditinterface.h"

#include "pluginloader.h"
#include "pluginmanager.h"
#include "aggregator.h"
#include "plugin.h"
#include "command.h"
#include "slapifactory.h"

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
    delete mDebugWindowInstance;
}

/*!
 * \brief Begin process of client initialization and starting.
 */
void SourceLineClient::start()
{
    mRemoteClient->connectToProvider(mConnectionId);
    mInterface = new TextEditInterface();
    connect(mInterface, &TextEditInterface::invoked, mRemoteClient, &RemoteApiClient::slotInvoke, Qt::UniqueConnection);
    QTimer::singleShot(0, this, SLOT(initPlugins()));
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

void SourceLineClient::initPlugins()
{
    // Plugin loading managing classes
    PluginLoader *lPluginLoader = new PluginLoader(this);

    mPluginManager = new PluginManager(this);
    mPluginManager->setPluginLoader(lPluginLoader);

    // TASK: Load plugin list from settings

    // Load plugins
    int lLoadedCount = 0;
    QStringList lActivePluginsList = mPluginManager->activePlugins();

    if (lActivePluginsList.isEmpty())
    {
        qDebug("        No plugin settings present: loading all available pluggins");
        lActivePluginsList = mPluginManager->availablePlugins();
    }

    foreach (const QString &lPluginId, lActivePluginsList)
    {
        qDebug("        Loading %s...", qPrintable(lPluginId));
        mPluginManager->loadPlugin(lPluginId);
        ++lLoadedCount;
    }

    Aggregator *a = SLAPIFactory::create(this);
    for (const QString &pluginId: mPluginManager->loadedPlugins())
    {
        Plugin *pluginInstance = mPluginManager->loadedPluginInstance(pluginId);
        if (pluginInstance)
        {
            pluginInstance->init(*a);
        }
    }

    for (QObject *o: a->contents())
    {
        connect(o, SIGNAL(invokeCommand(QByteArray, QVariant, QVariant, QVariant, QVariant, QVariant)),
            this, SLOT(apiCall(QByteArray,QVariant,QVariant,QVariant,QVariant,QVariant)), Qt::UniqueConnection);
    }

    PluginAPI *pluginApi = a->object<PluginAPI>();
    Q_CHECK_PTR(pluginApi);
    for (Command *command: pluginApi->commands(Commands::InitializeRepository))
    {
        command->init(*a);
    }
}

void SourceLineClient::apiCall(QByteArray signature, QVariant param1, QVariant param2,
                               QVariant param3, QVariant param4, QVariant param5)
{
    const QMetaObject *superclassMetaObj = sender()->metaObject()->superClass();
    if (superclassMetaObj)
    {
        QByteArray interfaceId = superclassMetaObj->className();
        mRemoteClient->slotInvoke(interfaceId, signature, param1, param2, param3, param4, param5);
    }
}

void SourceLineClient::test()
{
    mInterface->setText("Hello, SL!");
}

