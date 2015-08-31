#ifndef REVISIONTREEDOCK_H
#define REVISIONTREEDOCK_H

#include "genericdockwidget.h"

namespace Ui {
class RevisionTreeDock;
}

class RevisionTreeDock : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit RevisionTreeDock(QWidget *parent = 0);
    ~RevisionTreeDock();
    DockType type() const override;

private:
    Ui::RevisionTreeDock *ui;
};

#endif // REVISIONTREEDOCK_H
