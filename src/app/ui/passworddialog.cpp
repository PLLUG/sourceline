#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(username()));
    connect(this, SIGNAL(accepted()), this, SLOT(password()));
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

QString PasswordDialog::username()
{
    return ui->username->text();
}

QString PasswordDialog::password()
{
    return ui->password->text();
}
