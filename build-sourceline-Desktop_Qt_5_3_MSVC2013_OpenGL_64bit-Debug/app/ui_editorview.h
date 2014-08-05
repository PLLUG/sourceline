/********************************************************************************
** Form generated from reading UI file 'editorview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORVIEW_H
#define UI_EDITORVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorView
{
public:
    QLabel *label;

    void setupUi(QWidget *EditorView)
    {
        if (EditorView->objectName().isEmpty())
            EditorView->setObjectName(QStringLiteral("EditorView"));
        EditorView->resize(400, 300);
        label = new QLabel(EditorView);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 140, 131, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(EditorView);

        QMetaObject::connectSlotsByName(EditorView);
    } // setupUi

    void retranslateUi(QWidget *EditorView)
    {
        EditorView->setWindowTitle(QApplication::translate("EditorView", "Editor View", 0));
        label->setText(QApplication::translate("EditorView", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class EditorView: public Ui_EditorView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORVIEW_H
