#ifndef DOCKFILEVIEW_H
#define DOCKFILEVIEW_H

#include "genericdockwidget.h"

class QWidget;

namespace Ui {
class DockFileView;
}

class DockFileView : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit DockFileView(QWidget *parent = 0);
    ~DockFileView();
    DockType type() const;

public slots:
    void slotSetPage(int pPage);

private:
    Ui::DockFileView *ui;
};

#endif // FILEVIEW_H
