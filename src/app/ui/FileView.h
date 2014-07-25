#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include "genericdockwidget.h"

namespace Ui {
class FileView;
}

class FileView : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = 0);
    ~FileView();
    DockTypes::DockType type() const;
private:
    Ui::FileView *ui;
public slots:
    void slotSetPage(int pPage);
};

#endif // FILEVIEW_H
