#ifndef HISTORYTREE_H
#define HISTORYTREE_H

#include "genericdockwidget.h"

class QWidget;

namespace Ui {
class HistoryTree;
}

class HistoryTree : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit HistoryTree(QWidget *parent = 0);
    DockType type() const;
    ~HistoryTree();

private:
    Ui::HistoryTree *ui;

public slots:
    void slotSetPage(int pPage);
};

#endif // HISTORYTREE_H
