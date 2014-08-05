/********************************************************************************
** Form generated from reading UI file 'fileview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEVIEW_H
#define UI_FILEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileView
{
public:
    QLabel *label;

    void setupUi(QWidget *FileView)
    {
        if (FileView->objectName().isEmpty())
            FileView->setObjectName(QStringLiteral("FileView"));
        FileView->resize(400, 300);
        label = new QLabel(FileView);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 110, 101, 41));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);

        retranslateUi(FileView);

        QMetaObject::connectSlotsByName(FileView);
    } // setupUi

    void retranslateUi(QWidget *FileView)
    {
        FileView->setWindowTitle(QApplication::translate("FileView", "File View", 0));
        label->setText(QApplication::translate("FileView", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FileView: public Ui_FileView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEVIEW_H
