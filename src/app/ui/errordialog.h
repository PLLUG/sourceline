#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();

    void setTitleOfWindow(QString titleText);
    void setBriefErrorDescription(QString briefErrorText);
    void setFullErrorDescription(QString fullErrorText);

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
