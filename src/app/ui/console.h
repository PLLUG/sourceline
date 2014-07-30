#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include "genericdockwidget.h"
#include <string>
namespace Ui {
class Console;
}

class Console : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();
    DockTypes::DockType type() const;
private:
    Ui::Console *ui;
public slots:
    void slotSetPage(int pPage);
};

#endif // CONSOLE_H
