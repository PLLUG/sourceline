#include "mainwindow.h"
#include <QApplication>

#include "invocationbased.h"
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    QProcess client;
    QStringList args;
    args << "--id=sl";

    //This was hardcode. Use path to RemoteApiClient.exe on your computer.
    client.start("$$PWD/../../../bin/RemoteMetaConnector/RemoteApiClient.exe", args);

    return a.exec();
}
