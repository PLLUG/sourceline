/********************************************************************************
** Form generated from reading UI file 'viewsettingpage.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWSETTINGPAGE_H
#define UI_VIEWSETTINGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(245, 211);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox = new QCheckBox(Form);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_2 = new QCheckBox(Form);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(Form);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 0, 2, 1, 1);

        checkBox_4 = new QCheckBox(Form);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 1, 0, 1, 1);

        checkBox_5 = new QCheckBox(Form);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 1, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        checkBox->setText(QApplication::translate("Form", "File View", 0));
        checkBox_2->setText(QApplication::translate("Form", "Editor View", 0));
        checkBox_3->setText(QApplication::translate("Form", "Revision Tree", 0));
        checkBox_4->setText(QApplication::translate("Form", "Console", 0));
        checkBox_5->setText(QApplication::translate("Form", "History Tree", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWSETTINGPAGE_H
