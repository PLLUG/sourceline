/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout *gridLayout;
    QLabel *imageLabel;
    QLabel *versionLabel;
    QPushButton *updateButton;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *aboutTab;
    QGridLayout *gridLayout_2;
    QLabel *headingLabel_tabAbout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *logo1Label_tabAbout;
    QLabel *logo2Label_tabAbout;
    QLabel *textLabel_tabAbout;
    QWidget *gplTab;
    QGridLayout *gridLayout_3;
    QTextBrowser *textBrowser_tabGpl;
    QWidget *authorsTab;
    QGridLayout *gridLayout_4;
    QTextBrowser *textBrowser_tabAuthors;
    QWidget *pllugTab;
    QGridLayout *gridLayout_5;
    QLabel *headingLabel_tabPllug;
    QSpacerItem *horizontalSpacer_3;
    QLabel *logoLabel_tabPllug;
    QLabel *textLabel_tabPllug;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(540, 540);
        About->setMinimumSize(QSize(540, 450));
        About->setMaximumSize(QSize(600, 600));
        gridLayout = new QGridLayout(About);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imageLabel = new QLabel(About);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(0, 120));
        imageLabel->setMaximumSize(QSize(16777215, 150));
        imageLabel->setStyleSheet(QLatin1String("background-image: url(\":/splash/img/SL_Splash.png\");\n"
"background-position: center;"));

        gridLayout->addWidget(imageLabel, 0, 0, 1, 3);

        versionLabel = new QLabel(About);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));

        gridLayout->addWidget(versionLabel, 1, 0, 1, 1);

        updateButton = new QPushButton(About);
        updateButton->setObjectName(QStringLiteral("updateButton"));

        gridLayout->addWidget(updateButton, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        tabWidget = new QTabWidget(About);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        aboutTab = new QWidget();
        aboutTab->setObjectName(QStringLiteral("aboutTab"));
        gridLayout_2 = new QGridLayout(aboutTab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        headingLabel_tabAbout = new QLabel(aboutTab);
        headingLabel_tabAbout->setObjectName(QStringLiteral("headingLabel_tabAbout"));
        headingLabel_tabAbout->setMinimumSize(QSize(0, 100));
        headingLabel_tabAbout->setMaximumSize(QSize(16777215, 100));

        gridLayout_2->addWidget(headingLabel_tabAbout, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        logo1Label_tabAbout = new QLabel(aboutTab);
        logo1Label_tabAbout->setObjectName(QStringLiteral("logo1Label_tabAbout"));

        gridLayout_2->addWidget(logo1Label_tabAbout, 0, 2, 1, 1);

        logo2Label_tabAbout = new QLabel(aboutTab);
        logo2Label_tabAbout->setObjectName(QStringLiteral("logo2Label_tabAbout"));

        gridLayout_2->addWidget(logo2Label_tabAbout, 0, 3, 1, 1);

        textLabel_tabAbout = new QLabel(aboutTab);
        textLabel_tabAbout->setObjectName(QStringLiteral("textLabel_tabAbout"));
        textLabel_tabAbout->setScaledContents(false);
        textLabel_tabAbout->setWordWrap(false);

        gridLayout_2->addWidget(textLabel_tabAbout, 1, 0, 1, 4);

        tabWidget->addTab(aboutTab, QString());
        gplTab = new QWidget();
        gplTab->setObjectName(QStringLiteral("gplTab"));
        gridLayout_3 = new QGridLayout(gplTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textBrowser_tabGpl = new QTextBrowser(gplTab);
        textBrowser_tabGpl->setObjectName(QStringLiteral("textBrowser_tabGpl"));

        gridLayout_3->addWidget(textBrowser_tabGpl, 0, 0, 1, 1);

        tabWidget->addTab(gplTab, QString());
        authorsTab = new QWidget();
        authorsTab->setObjectName(QStringLiteral("authorsTab"));
        gridLayout_4 = new QGridLayout(authorsTab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        textBrowser_tabAuthors = new QTextBrowser(authorsTab);
        textBrowser_tabAuthors->setObjectName(QStringLiteral("textBrowser_tabAuthors"));

        gridLayout_4->addWidget(textBrowser_tabAuthors, 0, 0, 1, 1);

        tabWidget->addTab(authorsTab, QString());
        pllugTab = new QWidget();
        pllugTab->setObjectName(QStringLiteral("pllugTab"));
        gridLayout_5 = new QGridLayout(pllugTab);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        headingLabel_tabPllug = new QLabel(pllugTab);
        headingLabel_tabPllug->setObjectName(QStringLiteral("headingLabel_tabPllug"));

        gridLayout_5->addWidget(headingLabel_tabPllug, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(221, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        logoLabel_tabPllug = new QLabel(pllugTab);
        logoLabel_tabPllug->setObjectName(QStringLiteral("logoLabel_tabPllug"));
        logoLabel_tabPllug->setMinimumSize(QSize(0, 80));
        logoLabel_tabPllug->setMaximumSize(QSize(16777215, 80));

        gridLayout_5->addWidget(logoLabel_tabPllug, 0, 2, 1, 1);

        textLabel_tabPllug = new QLabel(pllugTab);
        textLabel_tabPllug->setObjectName(QStringLiteral("textLabel_tabPllug"));

        gridLayout_5->addWidget(textLabel_tabPllug, 1, 0, 1, 3);

        tabWidget->addTab(pllugTab, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 3);


        retranslateUi(About);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About Source Line", 0));
        imageLabel->setText(QString());
        versionLabel->setText(QApplication::translate("About", "Version 0.0.4 beta (build 000123)", 0));
        updateButton->setText(QApplication::translate("About", "Check for Updates", 0));
        headingLabel_tabAbout->setText(QApplication::translate("About", "<h1>Source Line</h1>\n"
"<h2>Crossplatform VCS Client</h2>", 0));
        logo1Label_tabAbout->setText(QApplication::translate("About", "<img src = \":/splash/img/sourceline.ico\" height = 80\n"
" />", 0));
        logo2Label_tabAbout->setText(QApplication::translate("About", "<img src = \":/splash/img/pllug.jpg\" height = 70 />", 0));
        textLabel_tabAbout->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(aboutTab), QApplication::translate("About", "About", 0));
        textBrowser_tabGpl->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(gplTab), QApplication::translate("About", "GPL v3", 0));
        textBrowser_tabAuthors->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(authorsTab), QApplication::translate("About", "Authors", 0));
        headingLabel_tabPllug->setText(QApplication::translate("About", "<h1>PLLUG Community</h1>", 0));
        logoLabel_tabPllug->setText(QApplication::translate("About", "<img src = \":/splash/img/pllug.jpg\" height = 70 />", 0));
        textLabel_tabPllug->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(pllugTab), QApplication::translate("About", "PLLUG", 0));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
