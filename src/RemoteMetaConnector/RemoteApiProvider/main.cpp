#include "mainwindow.h"
#include <QApplication>

#include "invocationbased.h"

#include "clientprocess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    ClientProcess client;
    client.setConnectionId("sl");
    client.setAllowClientDebugMode(true);
    client.start();

    return a.exec();
}
