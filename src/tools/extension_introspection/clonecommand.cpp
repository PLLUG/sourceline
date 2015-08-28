#include "clonecommand.h"
#include "aggregator.h"
#include "pluginapi.h"
#include "publicfileviewapi.h"

CloneCommand::CloneCommand(QObject *parent) : Command(parent)
{

}

QString CloneCommand::name() const
{
    return QStringLiteral("clone");
}

void CloneCommand::init(Aggregator &api)
{
    PluginAPI *pluginAPI = api.object<PluginAPI>();
    pluginAPI->slotRegisterCommand(this);

    PublicFileViewAPI *fileViewApi =  api.object<PublicFileViewAPI>();
    fileViewApi->addToMenu(name());
}

void CloneCommand::trigger()
{
    qDebug("CLONE!!!!!!!!!!!!");
}

void CloneCommand::processResult(Aggregator &api)
{

}

