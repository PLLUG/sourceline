#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    QCoreApplication::setOrganizationDomain("VK");
       QCoreApplication::setOrganizationName("Plug");
       QCoreApplication::setApplicationName("SourceLine");
       QCoreApplication::setApplicationVersion("1.0.0");
    app.setQuitOnLastWindowClosed(false);
    w.show();
    return app.exec();
}
