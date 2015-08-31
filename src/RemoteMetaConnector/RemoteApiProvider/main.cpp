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
    client.start("D:/PllPro/SL_ClientProvider/sourceline/src/build-remotemetaconnector-Desktop_Qt_5_5_0_MSVC2013_64bit-Debug/RemoteApiClient/debug/RemoteApiClient.exe", args);

    return a.exec();
}
