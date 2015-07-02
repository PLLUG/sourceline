#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QWidget>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
