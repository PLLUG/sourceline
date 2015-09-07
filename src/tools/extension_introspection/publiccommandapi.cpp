#include "publiccommandapi.h"

PublicCommandAPI::PublicCommandAPI(QString pCommandID, QObject *parent) :
    QObject(parent)
{
    mCommandID = pCommandID;
}

void PublicCommandAPI::trigger()
{
    emit invokeCommand(mCommandID, "trigger()");
}

