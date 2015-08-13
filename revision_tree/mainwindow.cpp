/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Halyna Butovych (galynabutovych@gmail.com)                    ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "revisionmodel.h"
#include "revisiontreewidget.h"
#include <QProcess>
#include <QDebug>
#include <QString>
#include "revisiontree.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mModel{new RevisionModel{this}},
    mProcess{new QProcess{this}}
{
    ui->setupUi(this);

    connect(mProcess, static_cast<void (QProcess::*)(int exitCode, QProcess::ExitStatus exitStatus)>(&QProcess::finished), this, [=]()
    {
        ui->centralWidget->setGraph(mModel->graph());
    });

    connect(mProcess,&QProcess::readyReadStandardOutput, this, [=]()
    {
        QStringList commits = QString(mProcess->readAllStandardOutput()).split("\n");
        QRegExp rxlen("\a([^,]*)\a \a([^,]*)\a \a([^,]*)\a \a([^,]*)\a \a([^,]*)\a \a([^,]*)\a");
        for(auto commit : commits)
        {
            int pos = rxlen.indexIn(commit);
            if (pos > -1) {
                qDebug() << "========================================================   ";
                QString hash = rxlen.cap(1);
                QString parents = rxlen.cap(2);
                QString author = rxlen.cap(3);
                QString email = rxlen.cap(4);
                QString time= rxlen.cap(5);
                QString message = rxlen.cap(6);

                qDebug() << "hash : " << hash;
                qDebug() << "author : " << author;
                qDebug() << "email : " << email;
                qDebug() << "time : " << QDateTime::fromTime_t(time.toInt());
                qDebug() << "message : " << message;

                RevisionNode newCommit = {
                    hash.toStdString(),
                    message.toStdString(),
                    author.toStdString(),
                    QDateTime::fromTime_t(time.toInt())
                };

                QStringList parentList = parents.split(" ");
                if(parentList.empty())
                {
                    // if no parents node has no parent, add empty string as parent
                    parentList << QString();
                }
                for(const auto &parent : parentList)
                {
                    qDebug() << "parent : " << parent;
                    mModel->addNode(parent.toStdString(), newCommit);
                }
            }
        }
    });

    QString program = "git";
    QStringList arguments;
    arguments << "log" << "--pretty=format:\"\a%H\a \a%P\a \a%an\a \a%ae\a \a%at\a \a%s\a%n\" ";

    mProcess->start(program, arguments);
}

MainWindow::~MainWindow()
{
    delete ui;
}
