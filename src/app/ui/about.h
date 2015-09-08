#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QString>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

    // TASK: add settng of verison
    // TASK: add version pri file

private:
    QString textFromFile(const QString &pAddress);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
