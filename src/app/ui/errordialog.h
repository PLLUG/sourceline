#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();

private slots:
    /*!
     * \brief on_pushButtonOk_clicked
     * After pushing close opened dialog
     * Maybe later will record info in log file
     */
    void on_pushButtonOk_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
