/********************************************************************************
** Form generated from reading UI file 'historytree.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYTREE_H
#define UI_HISTORYTREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryTree
{
public:
    QLabel *label;

    void setupUi(QWidget *HistoryTree)
    {
        if (HistoryTree->objectName().isEmpty())
            HistoryTree->setObjectName(QStringLiteral("HistoryTree"));
        HistoryTree->resize(400, 300);
        label = new QLabel(HistoryTree);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 120, 141, 61));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(HistoryTree);

        QMetaObject::connectSlotsByName(HistoryTree);
    } // setupUi

    void retranslateUi(QWidget *HistoryTree)
    {
        HistoryTree->setWindowTitle(QApplication::translate("HistoryTree", "History Tree", 0));
        label->setText(QApplication::translate("HistoryTree", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class HistoryTree: public Ui_HistoryTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYTREE_H
