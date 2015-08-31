#include "mainwindow.h"
#include <QCoreApplication>

#include "texteditinterface.h"
#include "remoteapiclient.h"
#include <QDebug>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Client");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Pass text to provider");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption idOption("id",
                                QCoreApplication::translate("main", "number"), "idValue");
    parser.addOption(idOption);
    parser.process(a);

    QString string = parser.value(idOption);
    //QStringList list = parser.values(idOption);

    TextEditInterface *mInterface = new TextEditInterface();
    RemoteApiClient *mRemoteClient = new RemoteApiClient();
    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::slotSetText, Qt::UniqueConnection);
    qDebug() << "Client started";

    QObject::connect(mInterface, &TextEditInterface::invoked, mRemoteClient, &RemoteApiClient::slotInvoke, Qt::UniqueConnection);
    mRemoteClient->connectToProvider("sl");
    mInterface->setText(string);

    return a.exec();
}
