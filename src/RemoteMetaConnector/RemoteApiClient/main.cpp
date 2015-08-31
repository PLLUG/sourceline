#include "mainwindow.h"
#include <QApplication>

#include "texteditinterface.h"
#include "remoteapiclient.h"
#include <QDebug>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextEditInterface *mInterface = new TextEditInterface();
    RemoteApiClient *mRemoteClient = new RemoteApiClient();
    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::slotSetText, Qt::UniqueConnection);
    qDebug() << "Client started";

    QObject::connect(mInterface, &TextEditInterface::invoked, mRemoteClient, &RemoteApiClient::slotInvoke, Qt::UniqueConnection);
    mRemoteClient->connectToProvider("sl");
    mInterface->setText("Text test from client . ");

    return a.exec();
}
