/********************************************************************************
** Form generated from reading UI file 'revisiontable.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVISIONTABLE_H
#define UI_REVISIONTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RevisionTable
{
public:
    QLabel *label;

    void setupUi(QWidget *RevisionTable)
    {
        if (RevisionTable->objectName().isEmpty())
            RevisionTable->setObjectName(QStringLiteral("RevisionTable"));
        RevisionTable->resize(400, 300);
        label = new QLabel(RevisionTable);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 110, 181, 71));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(RevisionTable);

        QMetaObject::connectSlotsByName(RevisionTable);
    } // setupUi

    void retranslateUi(QWidget *RevisionTable)
    {
        RevisionTable->setWindowTitle(QApplication::translate("RevisionTable", "Revision Table", 0));
        label->setText(QApplication::translate("RevisionTable", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class RevisionTable: public Ui_RevisionTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVISIONTABLE_H
