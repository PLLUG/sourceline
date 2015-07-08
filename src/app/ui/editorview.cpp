#include "editorview.h"
#include "ui_editorview.h"
#include "guidefs.h"

#include <QWidget>

EditorView::EditorView(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);
}

EditorView::~EditorView()
{
    delete ui;
}

DockType EditorView::type() const
{
    return DockType::EditorView;
}

void EditorView::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
