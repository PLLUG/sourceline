#include "testcommand.h"

TestCommand::TestCommand(QObject *parent) : QObject(parent)
{

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

}

void TestCommand::trigger(/*Aggregator &api*/)
{
    qDebug("!!!!!!");

}

void TestCommand::processResult(Aggregator &api)
{

}
