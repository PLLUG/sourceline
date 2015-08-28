#include "fileviewapi.h"
#include "commandmanager.h"
#include "file_view/fileview.h"

FileViewAPI::FileViewAPI(QObject *parent) : QObject(parent)
{

}

void FileViewAPI::setCommandManeger(CommandManager *pCommandManager)
{
    mCommandManager = pCommandManager;
}

void FileViewAPI::setFileView(FileView *pFileView)
{
    mFileView = pFileView;
}

void FileViewAPI::addToMenu(QString pCommandID)
{

}

