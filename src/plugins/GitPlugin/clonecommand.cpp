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
    IFileViewAPI *fileViewApi =  api.object<IFileViewAPI>();
    fileViewApi->addToMenu(name());
}

void CloneCommand::trigger()
{
    qDebug("CLONE!!!!!!!!!!!!");
}

void CloneCommand::processResult(Aggregator &api)
{
    Q_UNUSED(api)
}

