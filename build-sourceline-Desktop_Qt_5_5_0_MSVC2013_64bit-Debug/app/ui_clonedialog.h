/********************************************************************************
** Form generated from reading UI file 'clonedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLONEDIALOG_H
#define UI_CLONEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CloneDialog
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *mainTab;
    QGridLayout *gridLayout_3;
    QLabel *urlLabel;
    QLineEdit *urlLineEdit;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QLabel *cloneLabel;
    QLineEdit *cloneLineEdit;
    QPushButton *browseButton;
    QWidget *advancedTab;
    QGridLayout *gridLayout_4;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CloneDialog)
    {
        if (CloneDialog->objectName().isEmpty())
            CloneDialog->setObjectName(QStringLiteral("CloneDialog"));
        CloneDialog->resize(400, 288);
        gridLayout = new QGridLayout(CloneDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(CloneDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setTabShape(QTabWidget::Rounded);
        mainTab = new QWidget();
        mainTab->setObjectName(QStringLiteral("mainTab"));
        gridLayout_3 = new QGridLayout(mainTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(-1, 50, -1, 50);
        urlLabel = new QLabel(mainTab);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));

        gridLayout_3->addWidget(urlLabel, 0, 0, 1, 1);

        urlLineEdit = new QLineEdit(mainTab);
        urlLineEdit->setObjectName(QStringLiteral("urlLineEdit"));

        gridLayout_3->addWidget(urlLineEdit, 0, 1, 1, 1);

        comboBox = new QComboBox(mainTab);
        QIcon icon;
        icon.addFile(QStringLiteral(":/splash/Icons/gitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/splash/Icons/svnIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/splash/Icons/mercurialIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon2, QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_3->addWidget(comboBox, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 69, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 1, 1, 1);

        cloneLabel = new QLabel(mainTab);
        cloneLabel->setObjectName(QStringLiteral("cloneLabel"));

        gridLayout_3->addWidget(cloneLabel, 2, 0, 1, 1);

        cloneLineEdit = new QLineEdit(mainTab);
        cloneLineEdit->setObjectName(QStringLiteral("cloneLineEdit"));

        gridLayout_3->addWidget(cloneLineEdit, 2, 1, 1, 1);

        browseButton = new QPushButton(mainTab);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        gridLayout_3->addWidget(browseButton, 2, 2, 1, 1);

        tabWidget->addTab(mainTab, QString());
        advancedTab = new QWidget();
        advancedTab->setObjectName(QStringLiteral("advancedTab"));
        gridLayout_4 = new QGridLayout(advancedTab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        checkBox = new QCheckBox(advancedTab);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_4->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_2 = new QCheckBox(advancedTab);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_4->addWidget(checkBox_2, 1, 0, 1, 1);

        checkBox_3 = new QCheckBox(advancedTab);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_4->addWidget(checkBox_3, 2, 0, 1, 1);

        tabWidget->addTab(advancedTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CloneDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(CloneDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CloneDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CloneDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CloneDialog);
    } // setupUi

    void retranslateUi(QDialog *CloneDialog)
    {
        CloneDialog->setWindowTitle(QApplication::translate("CloneDialog", "Clone dialog", 0));
        urlLabel->setText(QApplication::translate("CloneDialog", "Url:", 0));
        comboBox->setItemText(0, QApplication::translate("CloneDialog", "Git", 0));
        comboBox->setItemText(1, QApplication::translate("CloneDialog", "SVN", 0));
        comboBox->setItemText(2, QApplication::translate("CloneDialog", "Mercurial", 0));

        cloneLabel->setText(QApplication::translate("CloneDialog", "Clone to:", 0));
        browseButton->setText(QApplication::translate("CloneDialog", "Browse...", 0));
        tabWidget->setTabText(tabWidget->indexOf(mainTab), QApplication::translate("CloneDialog", "Main", 0));
        checkBox->setText(QApplication::translate("CloneDialog", "Option 1", 0));
        checkBox_2->setText(QApplication::translate("CloneDialog", "Option 2", 0));
        checkBox_3->setText(QApplication::translate("CloneDialog", "Option 3", 0));
        tabWidget->setTabText(tabWidget->indexOf(advancedTab), QApplication::translate("CloneDialog", "Advanced", 0));
    } // retranslateUi

};

namespace Ui {
    class CloneDialog: public Ui_CloneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLONEDIALOG_H
