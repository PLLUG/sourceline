#include "clonecommand.h"

CloneCommand::CloneCommand(QObject *parent) : Command(parent)
{
    commandName = "Clone";
    setIcon(QIcon(":/splash/img/Clone.ico"));
}

void CloneCommand::init(Aggregator &api)
{

}

void CloneCommand::trigger(Aggregator &api)
{

}

void CloneCommand::processResult(Aggregator &api)
{

}
