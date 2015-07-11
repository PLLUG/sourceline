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

    /*!
     * \brief Set title of window for given parameter
     * \param titleText is text of title which need to set
     */
    void setTitleOfWindow(const QString &titleText);

    /*!
     * \brief Set brief error description with given text
     * \param briefErrorText is brief error's description
     */
    void setBriefErrorDescription(const QString &briefErrorText);

    /*!
     * \brief Set full error description with given text
     * \param fullErrorText is full error's description
     */
    void setFullErrorDescription(const QString &fullErrorText);

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
