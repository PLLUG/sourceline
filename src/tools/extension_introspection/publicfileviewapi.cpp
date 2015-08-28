#include "publicfileviewapi.h"
#include "invocationbased.h"
#include "fileviewapi.h"

PublicFileViewAPI::PublicFileViewAPI(QObject *parent) : QObject(parent)
{

}

void PublicFileViewAPI::addToMenu(QString commandId)
{
    emit invokeCommand("addToMenu(QString)", commandId);
}

