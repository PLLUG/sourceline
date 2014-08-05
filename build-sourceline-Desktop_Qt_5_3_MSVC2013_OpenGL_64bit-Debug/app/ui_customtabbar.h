/********************************************************************************
** Form generated from reading UI file 'customtabbar.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMTABBAR_H
#define UI_CUSTOMTABBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomTabBar
{
public:

    void setupUi(QWidget *CustomTabBar)
    {
        if (CustomTabBar->objectName().isEmpty())
            CustomTabBar->setObjectName(QStringLiteral("CustomTabBar"));
        CustomTabBar->resize(400, 300);

        retranslateUi(CustomTabBar);

        QMetaObject::connectSlotsByName(CustomTabBar);
    } // setupUi

    void retranslateUi(QWidget *CustomTabBar)
    {
        CustomTabBar->setWindowTitle(QApplication::translate("CustomTabBar", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomTabBar: public Ui_CustomTabBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMTABBAR_H
