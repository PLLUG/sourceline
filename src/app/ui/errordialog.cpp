#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

    ui->labelBriefErrorText->setWordWrap(true);        
    ui->plainTextEditFullErrorText->setStyleSheet("border: 2px solid black");

    connect(ui->buttonBoxOk, SIGNAL(accepted()),this,SLOT(accept()));
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::setTitleOfWindow(const QString &pTitleText)
{
    setWindowTitle(pTitleText);
}

void ErrorDialog::setBriefErrorDescription(const QString &pBriefErrorText)
{
    ui->labelBriefErrorText->setText(pBriefErrorText);
}

void ErrorDialog::setFullErrorDescription(const QString &pFullErrorText)
{
    ui->plainTextEditFullErrorText->setPlainText(pFullErrorText);
}
