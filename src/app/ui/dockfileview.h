#ifndef DOCKFILEVIEW_H
#define DOCKFILEVIEW_H

#include <QWidget>
#include "genericdockwidget.h"

namespace Ui {
class DockFileView;
}

class DockFileView : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit DockFileView(QWidget *parent = 0);
    ~DockFileView();
    DockTypes::DockType type() const;
private:
    Ui::DockFileView *ui;

public slots:
    void slotSetPage(int pPage);
};

#endif // FILEVIEW_H
