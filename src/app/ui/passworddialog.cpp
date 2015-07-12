#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QDebug>

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::accept()
{
    qDebug() << "accept";
    PasswordDialog::~PasswordDialog();
}

void PasswordDialog::reject()
{
    qDebug() << "reject";
    PasswordDialog::~PasswordDialog();
}
