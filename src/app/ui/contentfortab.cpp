#include "contentfortab.h"
#include "ui_contentfortab.h"
#include "components/console/consoleview.h"
#include "ui/dockconsole.h"
#include "ui/dockfileview.h"
#include "ui/editorview.h"
#include "ui/revisiontreedock.h"
#include "../components/file_view/fileview.h"
#include "components/revision_tree/revisiontree.h"

#include <QProcess>

ContentForTab::ContentForTab(QWidget *parent) :
    QMainWindow(parent)
  ,ui(new Ui::ContentForTab)
  ,mHistoryTree{new RevisionTreeDock{this}}
  ,mRevisionTreeContents{new RevisionTree{mHistoryTree}}
  ,mEditorView{new EditorView{this}}
  ,mFileView{new DockFileView{this}}
  ,mFileViewContents{new FileView{mFileView}}
  ,mConsole{new DockConsole{this}}
  ,mConsoleContents{new ConsoleView{mConsole}}

{
    ui->setupUi(this);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
    setMouseTracking(false);
    setAutoFillBackground(false);
    setDockNestingEnabled(true);
    setDockOptions(QMainWindow::AllowNestedDocks
                   |QMainWindow::AllowTabbedDocks
                   |QMainWindow::AnimatedDocks);

    //COMMENT: Create DockWidget HistoryTree, set content for it and add this HistoryTree to ContentForTabWorkplace
    mHistoryTree->setWidget(mRevisionTreeContents);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, mHistoryTree);

    //COMMENT: Create DockWidget EditorView and add this EditorView to ContentForTabWorkplace
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, mEditorView);

    //COMMENT: Create DockWidget DockFileView, set content for it and add this DockFileView to ContentForTabWorkplace
    mFileView->setWidget(mFileViewContents);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, mFileView);

    //COMMENT: Create DockWidget DockConsole, set content for it and add this DockConsole to ContentForTabWorkplace
    mConsole->setLayoutDirection(Qt::LeftToRight);
    mConsole->setWidget(mConsoleContents);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, mConsole);

    splitDockWidget(mEditorView, mConsole, Qt::Vertical);
    tabifyDockWidget(mEditorView, mFileView);


    // TODO: move to git log command
    QProcess *mProcess{new QProcess{this}};

    connect(mProcess, static_cast<void (QProcess::*)(int exitCode, QProcess::ExitStatus exitStatus)>(&QProcess::finished), this, [=]()
    {
        mRevisionTreeContents->read();
    });

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

            RevisionNode newCommit = {
                hash.toStdString(),
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
                mRevisionTreeContents->addNode(parent.toStdString(), newCommit);
            }
            mRevisionTreeContents->putProperty(hash.toStdString(),"author",author);
            mRevisionTreeContents->putProperty(hash.toStdString(),"email",email);
            mRevisionTreeContents->putProperty(hash.toStdString(),"time",QDateTime::fromTime_t(time.toInt()));
            mRevisionTreeContents->putProperty(hash.toStdString(),"message",message);
        }
    });

    QString program = "git";
    QStringList arguments;
    arguments << "log" << "--pretty=format:%H\a%P\a%an\a%ae\a%at\a%s\a%n";

    mProcess->start(program, arguments);
}

ContentForTab::~ContentForTab()
{
    delete ui;
}

