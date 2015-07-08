#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

    setFixedSize(400,300);
    setMinimumSize(400,300);
    setMaximumSize(600,400);

    QPixmap iconExclamation(":Icons/Icons/exclamation.png");
    ui->labelIconExclamation->setPixmap(iconExclamation);

    ui->labelBriefErrorText->setWordWrap(true);

    ui->labelFullErrorText->setWordWrap(true);
    ui->labelFullErrorText->setStyleSheet("border: 2px solid black");

    connect(ui->buttonBoxOk, SIGNAL(accepted()),this,SLOT(close()));
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::setTitleOfWindow(const QString &titleText)
{
    setWindowTitle(titleText);
}

void ErrorDialog::setBriefErrorDescription(const QString &briefErrorText)
{
    ui->labelBriefErrorText->setText(briefErrorText);
}

void ErrorDialog::setFullErrorDescription(const QString &fullErrorText)
{
    ui->labelFullErrorText->setText(fullErrorText);
}
