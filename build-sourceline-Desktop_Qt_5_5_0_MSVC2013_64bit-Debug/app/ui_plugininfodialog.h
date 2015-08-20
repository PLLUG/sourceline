/********************************************************************************
** Form generated from reading UI file 'plugininfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGININFODIALOG_H
#define UI_PLUGININFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_PluginInfoDialog
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *PluginInfoDialog)
    {
        if (PluginInfoDialog->objectName().isEmpty())
            PluginInfoDialog->setObjectName(QStringLiteral("PluginInfoDialog"));
        PluginInfoDialog->resize(381, 271);
        gridLayout = new QGridLayout(PluginInfoDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(PluginInfoDialog);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(145, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        okButton = new QPushButton(PluginInfoDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(144, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        retranslateUi(PluginInfoDialog);

        QMetaObject::connectSlotsByName(PluginInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *PluginInfoDialog)
    {
        PluginInfoDialog->setWindowTitle(QApplication::translate("PluginInfoDialog", "Dialog", 0));
        okButton->setText(QApplication::translate("PluginInfoDialog", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class PluginInfoDialog: public Ui_PluginInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGININFODIALOG_H
