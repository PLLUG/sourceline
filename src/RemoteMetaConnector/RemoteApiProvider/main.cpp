#include "mainwindow.h"
#include <QApplication>

#include "invocationbased.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    return a.exec();
}
