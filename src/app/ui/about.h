#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About *ui;

    QString textFromFile(QString address);
};

#endif // ABOUT_H
