#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include "genericdockwidget.h"
#include <string>
namespace Ui {
class DockConsole;
}

class DockConsole : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit DockConsole(QWidget *parent = 0);
    ~DockConsole();
    DockTypes::DockType type() const;
private:
    Ui::DockConsole *ui;
public slots:
    void slotSetPage(int pPage);
};

#endif // CONSOLE_H
