#include "mainwindow.h"
#include <QApplication>

#include "invocationbased.h"
#include <QProcess>
#include <QDebug>

static const QString SL_CLIENT_EXECUTABLE_NAME("slclient");
#ifdef Q_OS_WIN
static const QString SL_CLIENT_EXECUTABLE_EXTENSION(".exe");
#else
static const QString SL_CLIENT_EXECUTABLE_EXTENSION("");
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initInvocationBasedClasses();

    MainWindow w;
    w.show();

    QProcess client;
    QStringList args;
    args << "--id";
    args << "sl";
    args << "--debug";

    // SL client should be located in the same directory as SL executable
    QString slClientPath = QString("%1/%2").arg(QApplication::applicationDirPath(), SL_CLIENT_EXECUTABLE_NAME);
    if (!SL_CLIENT_EXECUTABLE_EXTENSION.isEmpty())
    {
        slClientPath.append(SL_CLIENT_EXECUTABLE_EXTENSION);
    }

    client.startDetached(slClientPath, args);
    client.waitForStarted();
    if (client.state() == QProcess::Running)
    {
        qDebug("Running!");
    } else {
        qDebug() << client.errorString() << slClientPath;
    }

    return a.exec();
}
