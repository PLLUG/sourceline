#include "pluginapi.h"

PluginAPI::PluginAPI(QObject *parent)
    : QObject(parent)
    , mCommandManager{nullptr}
{

}

void PluginAPI::setCommandManager(CommandManager *commandManager)
{
    mCommandManager = commandManager;
}

void PluginAPI::registerCommandId(QString commandId)
{

}



