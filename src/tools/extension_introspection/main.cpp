#include "mainwindow.h"
#include <QApplication>
#include "invocationbased.h"
#include "clientprocess.h"
#include "remoteapiprovider.h"
#include "commandmanager.h"

#include "fileviewapi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    InvocationBased *fileViewInvocationBased = new InvocationBased(&w);
    fileViewInvocationBased->setTarget(w.api());

    InvocationBased *commandApiInvocationBased = new InvocationBased(&w);
    commandApiInvocationBased->setTarget(w.commandManager());

    RemoteApiProvider *apiProvider = new RemoteApiProvider(&a);
    apiProvider->addApiProvider(fileViewInvocationBased);
    apiProvider->addApiProvider(commandApiInvocationBased);

    ClientProcess client(*apiProvider);
    client.setConnectionId("sl");
    client.setAllowClientDebugMode(true);
    client.start();

    return a.exec();
}
