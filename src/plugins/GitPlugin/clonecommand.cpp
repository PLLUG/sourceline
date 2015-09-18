#include "clonecommand.h"
#include "aggregator.h"
//#include "pluginapi.h"
//#include "publicfileviewapi.h"

#include "ifileviewapi.h"

CloneCommand::CloneCommand(QObject *parent) : Command(parent)
{

}

QString CloneCommand::name() const
{
    return QStringLiteral("clone");
}

void CloneCommand::init(Aggregator &api)
{
//    PluginAPI *pluginAPI = api.object<PluginAPI>();
//    pluginAPI->slotRegisterCommand(this);

    IFileViewAPI *fileViewApi =  api.object<IFileViewAPI>();
    fileViewApi->addToMenu(name());
}

void CloneCommand::trigger()
{
    qDebug("CLONE!!!!!!!!!!!!");
}

void CloneCommand::processResult(Aggregator &api)
{

}

