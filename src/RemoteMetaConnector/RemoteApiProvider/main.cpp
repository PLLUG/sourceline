#include "mainwindow.h"

#include <QApplication>
#include <QPlainTextEdit>

#include "invocationbased.h"
#include "remoteapiprovider.h"
#include "clientprocess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    RemoteApiProvider *apiProvider = new RemoteApiProvider(&a);

    InvocationBased *textInvoker = new InvocationBased;
    textInvoker->setTarget(&w.textEdit());
    apiProvider->addApiProvider(textInvoker);

    ClientProcess client(*apiProvider);
    client.setConnectionId("sl");
    client.setAllowClientDebugMode(true);
    client.start();

    return a.exec();
}
