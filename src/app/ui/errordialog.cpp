#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);    
    this->setFixedSize(400,300);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
    connect(pushButtonOk,SIGNAL(clicked(bool)),this,SLOT(on_pushButtonOk_clicked()));
}

void ErrorDialog::on_pushButtonOk_clicked()
{
    this->close();
}
