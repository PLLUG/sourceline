#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class CloneDialog;
}

class CloneDialog : public QDialog
{
    Q_OBJECT

public:
    CloneDialog(QWidget *parent = 0);
    ~CloneDialog();

private slots:
    void browse();

private:
    Ui::CloneDialog *ui;
};

#endif // CLONEDIALOG_H
