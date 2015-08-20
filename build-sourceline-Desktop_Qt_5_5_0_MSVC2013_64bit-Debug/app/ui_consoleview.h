/********************************************************************************
** Form generated from reading UI file 'consoleview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEVIEW_H
#define UI_CONSOLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "ui/console/console.h"

QT_BEGIN_NAMESPACE

class Ui_ConsoleView
{
public:
    QGridLayout *gridLayout;
    Console *plainTextEdit;

    void setupUi(QWidget *ConsoleView)
    {
        if (ConsoleView->objectName().isEmpty())
            ConsoleView->setObjectName(QStringLiteral("ConsoleView"));
        ConsoleView->resize(400, 300);
        gridLayout = new QGridLayout(ConsoleView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new Console(ConsoleView);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);


        retranslateUi(ConsoleView);

        QMetaObject::connectSlotsByName(ConsoleView);
    } // setupUi

    void retranslateUi(QWidget *ConsoleView)
    {
        ConsoleView->setWindowTitle(QApplication::translate("ConsoleView", "ConsoleView", 0));
    } // retranslateUi

};

namespace Ui {
    class ConsoleView: public Ui_ConsoleView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEVIEW_H
