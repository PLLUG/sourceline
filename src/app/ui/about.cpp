#include "about.h"
#include "ui_about.h"

// TASK: rename class to AboutDialog
About::About(QWidget *parent) :
    QDialog(parent,
              Qt::WindowSystemMenuHint
            | Qt::WindowTitleHint
            | Qt::WindowCloseButtonHint),
    ui(new Ui::About)
{
    ui->setupUi(this);

    //ui->imageLabel->setPixmap(QPixmap(":/splash/img/SL_Splash.png"));

    ui->textLabel_tabAbout->setText(textFromFile(":/text/txt/about-dialog/About.txt"));
    ui->textBrowser_tabGpl->setText(textFromFile(":/text/txt/about-dialog/GPL v3.txt"));
    ui->textBrowser_tabAuthors->setText(textFromFile(":/text/txt/about-dialog/Authors.txt"));
    ui->textLabel_tabPllug->setText(textFromFile(":/text/txt/about-dialog/PLLUG.txt"));

    ui->textLabel_tabAbout->setAlignment(Qt::AlignTop);
    ui->textLabel_tabPllug->setAlignment(Qt::AlignTop);

    ui->textLabel_tabAbout->setWordWrap(true);
    ui->textLabel_tabPllug->setWordWrap(true);
}

About::~About()
{
    delete ui;
}

QString About::textFromFile(QString address)
{
    QFile file(address);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString("Cannot open ") + address;
        return QString();
    }

    QTextStream in(&file);
    QString rText = in.readAll();

    return rText;
}
