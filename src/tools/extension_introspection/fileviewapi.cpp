#include "fileviewapi.h"
#include "commandmanager.h"

FileViewAPI::FileViewAPI(QObject *parent) : QObject(parent)
{

}

void FileViewAPI::setCommandManeger(CommandManager *pCommandManager)
{
    mCommandManager = pCommandManager;
}

void FileViewAPI::addToMenu(QString pCommandID)
{

}

