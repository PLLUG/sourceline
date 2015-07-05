#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = 0);
    ~PasswordDialog();

private slots:
    /*!
     * \brief Close password dialog
     */
    void on_cancelButton_clicked();

    /*!
     * \brief Close password dialog
     * Later it will check login and password
     * If everything is correct then close password dialog,
     * else show error dialog
     */
    void on_loginButton_clicked();

private:
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
