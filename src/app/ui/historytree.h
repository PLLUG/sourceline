#ifndef HISTORYTREE_H
#define HISTORYTREE_H

#include "genericdockwidget.h"

class QWidget;
class QTimer;

namespace Ui {
class HistoryTree;
}

class HistoryTree : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit HistoryTree(QWidget *parent = 0);
    DockTypes::DockType type() const;
    ~HistoryTree();

public slots:
    void slotSetPage(int pPage);

private:
    Ui::HistoryTree *ui;
};

#endif // HISTORYTREE_H
