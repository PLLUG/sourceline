#include "ui\errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}
