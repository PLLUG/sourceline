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

    this->setMinimumSize(400,300);
    this->setMaximumSize(600,400);

    QPixmap iconExclamation(":Icons/Icons/exclamation.png");
    ui->labelIconExclamation->setPixmap(iconExclamation);

    ui->labelBriefErrorText->setWordWrap(true);

    ui->labelFullErrorText->setWordWrap(true);
    ui->labelFullErrorText->setStyleSheet("border: 2px solid black");

    connect(ui->buttonBoxOk, SIGNAL(accepted()),this,SLOT(close()));
}

void ErrorDialog::setTitleOfWindow(QString titleText)
{
    this->setWindowTitle(titleText);
}

void ErrorDialog::setBriefErrorDescription(QString briefErrorText)
{
    ui->labelBriefErrorText->setText(briefErrorText);
}

void ErrorDialog::setFullErrorDescription(QString fullErrorText)
{
    ui->labelFullErrorText->setText(fullErrorText);
}
