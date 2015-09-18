#include "fileviewapi.h"
#include "commandmanager.h"
#include "file_view/fileview.h"
#include <QAction>
#include "publiccommandapi.h"

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
    PublicCommandAPI *commandApi = mCommandManager->command(pCommandID);
    QAction* actionForCommand = new QAction(this);
    actionForCommand->setText(pCommandID);
    connect(actionForCommand, SIGNAL(triggered(bool)), commandApi, SLOT(trigger()), Qt::UniqueConnection);
    mFileView->registerAction(actionForCommand,FileView::NoneSelection);
}

