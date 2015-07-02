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
    /*!
     * \brief connect
     * Connect performs slot on_pushButtonOk_clicked() after pushing on button Ok
     */
    connect(pushButtonOk,SIGNAL(clicked(bool)),this,SLOT(on_pushButtonOk_clicked()));
}

void ErrorDialog::on_pushButtonOk_clicked()
{
    this->close();
}
