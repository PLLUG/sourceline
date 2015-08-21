#include "passworddialog.h"
#include "ui_passworddialog.h"
#include "QDebug"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

QString PasswordDialog::username() const
{
    return ui->username->text();
}

QString PasswordDialog::password() const
{
    return ui->password->text();
}
