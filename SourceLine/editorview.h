#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QWidget>
#include "genericdockwidget.h"

namespace Ui {
class EditorView;
}

class EditorView : public GenericDockWidget
{
    Q_OBJECT

public:
    explicit EditorView(QWidget *parent = 0);
    DockTypes::DockType type() const;
    ~EditorView();

private:
    Ui::EditorView *ui;

public slots:
    void slotSetPage(int pPage);
};

#endif // EDITORVIEW_H