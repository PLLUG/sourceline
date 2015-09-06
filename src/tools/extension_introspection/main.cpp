#include "mainwindow.h"
#include <QApplication>
#include "invocationbased.h"
#include "clientprocess.h"
#include "remoteapiprovider.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    RemoteApiProvider *apiProvider = new RemoteApiProvider(&a);

    ClientProcess client(*apiProvider);
    client.setConnectionId("sl");
    client.setAllowClientDebugMode(true);
    client.start();

    return a.exec();
}
