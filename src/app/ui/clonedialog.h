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
    explicit CloneDialog(QWidget *parent = 0);
    ~CloneDialog();

private slots:
    /*!
     * \brief Opens file dialog, in which user selects proper directory.
     * After selecting, full path of selected directory is shown in lineEdit "Clone to:".
     * If user pressed "Cancel" button, nothing is changed in lineEdit.
     */
    void browse();

private:
    Ui::CloneDialog *ui;
};

#endif // CLONEDIALOG_H
