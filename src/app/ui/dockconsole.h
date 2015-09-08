#ifndef CONSOLE_H
#define CONSOLE_H

#include "genericdockwidget.h"

class QWidget;

namespace Ui {
class DockConsole;
}

class DockConsole : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit DockConsole(QWidget *parent = 0);
    ~DockConsole();
    DockType type() const;

public slots:
    void slotSetPage(int pPage);

private:
    Ui::DockConsole *ui;
};

#endif // CONSOLE_H
