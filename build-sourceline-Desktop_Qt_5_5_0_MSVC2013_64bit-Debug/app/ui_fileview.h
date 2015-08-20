/********************************************************************************
** Form generated from reading UI file 'fileview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEVIEW_H
#define UI_FILEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ui/fileview/iconizedlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_FileView
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    IconizedLineEdit *lineEdit;
    QListView *listView;

    void setupUi(QWidget *FileView)
    {
        if (FileView->objectName().isEmpty())
            FileView->setObjectName(QStringLiteral("FileView"));
        FileView->resize(368, 270);
        gridLayout = new QGridLayout(FileView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit = new IconizedLineEdit(FileView);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit->setReadOnly(true);

        verticalLayout->addWidget(lineEdit);

        listView = new QListView(FileView);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(FileView);

        QMetaObject::connectSlotsByName(FileView);
    } // setupUi

    void retranslateUi(QWidget *FileView)
    {
        FileView->setWindowTitle(QApplication::translate("FileView", "FileView", 0));
    } // retranslateUi

};

namespace Ui {
    class FileView: public Ui_FileView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEVIEW_H
