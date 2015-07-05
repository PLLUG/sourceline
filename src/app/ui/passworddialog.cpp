#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    this->setFixedSize(300, 200);
    this->setWindowTitle("Log in");
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_cancelButton_clicked()
{
    this->close();
}

void PasswordDialog::on_loginButton_clicked()
{
    this->close();
}
