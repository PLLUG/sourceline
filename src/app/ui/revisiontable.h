#ifndef REVISIONTABLE_H
#define REVISIONTABLE_H

#include "genericdockwidget.h"

class QWidget;

namespace Ui {
class RevisionTable;
}

class RevisionTable : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit RevisionTable(QWidget *parent = 0);
    DockTypes::DockType type() const;
    ~RevisionTable();

private:
    Ui::RevisionTable *ui;

public slots:
    void slotSetPage(int pPage);
};

#endif // REVISIONTABLE_H
