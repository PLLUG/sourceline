/********************************************************************************
** Form generated from reading UI file 'dockconsole.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKCONSOLE_H
#define UI_DOCKCONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockConsole
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *DockConsole)
    {
        if (DockConsole->objectName().isEmpty())
            DockConsole->setObjectName(QStringLiteral("DockConsole"));
        DockConsole->resize(335, 354);
        gridLayout = new QGridLayout(DockConsole);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(DockConsole);

        QMetaObject::connectSlotsByName(DockConsole);
    } // setupUi

    void retranslateUi(QWidget *DockConsole)
    {
        DockConsole->setWindowTitle(QApplication::translate("DockConsole", "Console", 0));
    } // retranslateUi

};

namespace Ui {
    class DockConsole: public Ui_DockConsole {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKCONSOLE_H
