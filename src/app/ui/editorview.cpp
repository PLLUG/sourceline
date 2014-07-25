#include "editorview.h"
#include "ui_editorview.h"
#include "guidefs.h"

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

DockTypes::DockType EditorView::type() const
{
    return DockTypes::EditorView;
}

void EditorView::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
