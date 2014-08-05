/********************************************************************************
** Form generated from reading UI file 'files.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILES_H
#define UI_FILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Files
{
public:

    void setupUi(QWidget *Files)
    {
        if (Files->objectName().isEmpty())
            Files->setObjectName(QStringLiteral("Files"));
        Files->resize(400, 300);

        retranslateUi(Files);

        QMetaObject::connectSlotsByName(Files);
    } // setupUi

    void retranslateUi(QWidget *Files)
    {
        Files->setWindowTitle(QApplication::translate("Files", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Files: public Ui_Files {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILES_H
