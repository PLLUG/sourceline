/********************************************************************************
** Form generated from reading UI file 'console.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QLabel *label;

    void setupUi(QWidget *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QStringLiteral("Console"));
        Console->resize(335, 354);
        label = new QLabel(Console);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 150, 121, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(Console);

        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QWidget *Console)
    {
        Console->setWindowTitle(QApplication::translate("Console", "Console", 0));
        label->setText(QApplication::translate("Console", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
