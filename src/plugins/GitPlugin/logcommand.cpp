#include "logcommand.h"
#include <QProcess>
#include <QDebug>
#include <QDateTime>

LogCommand::LogCommand(QObject *parent) : Command(parent)
{

}

QString LogCommand::name() const
{
    return QStringLiteral("log");
}

void LogCommand::init(Aggregator &api)
{
    mProcess = new QProcess{this};
}

void LogCommand::trigger()
{

//    connect(mProcess, static_cast<void (QProcess::*)(int exitCode, QProcess::ExitStatus exitStatus)>(&QProcess::finished),
//    this,0);

    connect(mProcess,&QProcess::readyReadStandardOutput, this, [=]()
    {
        QStringList commits = QString(mProcess->readAllStandardOutput()).split("\n",QString::SkipEmptyParts);
        QRegExp rxlen("([^,]*)\a([^,]*)\a([^,]*)\a([^,]*)\a([^,]*)\a([^,]*)\a");
        for(auto commit : commits)
        {
            QString hash = rxlen.cap(1);
            QString parents = rxlen.cap(2);
            QString author = rxlen.cap(3);
            QString email = rxlen.cap(4);
            QString time= rxlen.cap(5);
            QString message = rxlen.cap(6);
            QStringList dataList = commit.split("\a");
            if(!dataList.empty() && dataList.count() >= 5)
            {
                hash = dataList.at(0);
                parents = dataList.at(1);
                author = dataList.at(2);
                email = dataList.at(3);
                time= dataList.at(4);
                message = dataList.at(5);
            }
            qDebug() << author << email << QDateTime::fromTime_t(time.toInt()) << message;
        }
    });

    QString program = "git";
    QStringList arguments;
    arguments << "log" << "--pretty=format:%H\a%P\a%an\a%ae\a%at\a%s\a%n";

    mProcess->start(program, arguments);
}

void LogCommand::processResult(Aggregator &api)
{

}

