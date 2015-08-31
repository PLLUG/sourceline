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
    args << "--id=1234567890";
    client.start("C:/sourceline/src/build-remotemetaconnector-Desktop_Qt_5_5_0_MinGW_32bit-Debug/RemoteApiClient/debug/RemoteApiClient.exe", args);

    return a.exec();
}
