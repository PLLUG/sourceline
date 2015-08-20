/********************************************************************************
** Form generated from reading UI file 'dockfileview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKFILEVIEW_H
#define UI_DOCKFILEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockFileView
{
public:

    void setupUi(QWidget *DockFileView)
    {
        if (DockFileView->objectName().isEmpty())
            DockFileView->setObjectName(QStringLiteral("DockFileView"));
        DockFileView->resize(400, 300);

        retranslateUi(DockFileView);

        QMetaObject::connectSlotsByName(DockFileView);
    } // setupUi

    void retranslateUi(QWidget *DockFileView)
    {
        DockFileView->setWindowTitle(QApplication::translate("DockFileView", "File View", 0));
    } // retranslateUi

};

namespace Ui {
    class DockFileView: public Ui_DockFileView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKFILEVIEW_H
