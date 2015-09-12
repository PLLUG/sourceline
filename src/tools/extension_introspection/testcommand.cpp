#include "testcommand.h"
#include "aggregator.h"
#include "pluginapi.h"

TestCommand::TestCommand(QObject *parent) : Command(parent)
{

}

QString TestCommand::name() const
{
    return mName;
}

/// To register command:
///  * class PluginAPI
///      * method register(Command *)
///          * add command id and InvocableBased to hash
///          * emit signal with id - new Command registered
///  * class PublicCommandAPI - for Command class
///      * method trigger()
///           * emit invoke() with : command id, "triggered()" signature and no  parameters
///
///  (1) new PublicCommandAPI for id <- CommandManager::slotCommandRegistered() <- ( emit commandRegistered( id ) ) <- PluginAPI::register(TestCommand *)
///  (2) PublicCommandAPI -> ( emit invoke() ) -> PluginAPI -> ( InvocableBased->invoke() ) -> TestCommand::triggered()




void TestCommand::init(Aggregator &api)
{

//    api.registerCommand(this);
    PluginAPI *pluginAPI = api.object<PluginAPI>();
    pluginAPI->slotRegisterCommand(this);
}

void TestCommand::trigger(/*Aggregator &api*/)
{
    qDebug("!!!!!!");

}

void TestCommand::processResult(Aggregator &api)
{
    Q_UNUSED(api)
}
