#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "boost/concept_check.hpp"
#include "revisionnode.h"
#include "checktypes.h"

int main(int argc, char *argv[])
{
    Checker<RevisionNode> ch;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
