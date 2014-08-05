/********************************************************************************
** Form generated from reading UI file 'appsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPSETTINGSDIALOG_H
#define UI_APPSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AppSettingsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnApply;

    void setupUi(QDialog *AppSettingsDialog)
    {
        if (AppSettingsDialog->objectName().isEmpty())
            AppSettingsDialog->setObjectName(QStringLiteral("AppSettingsDialog"));
        AppSettingsDialog->resize(601, 434);
        gridLayout = new QGridLayout(AppSettingsDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(AppSettingsDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(150, 0));
        listWidget->setMaximumSize(QSize(150, 16777215));
        listWidget->setIconSize(QSize(40, 45));

        verticalLayout->addWidget(listWidget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        stackedWidget = new QStackedWidget(AppSettingsDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(425, 0));

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnOk = new QPushButton(AppSettingsDialog);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        horizontalLayout_2->addWidget(btnOk);

        btnCancel = new QPushButton(AppSettingsDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);

        btnApply = new QPushButton(AppSettingsDialog);
        btnApply->setObjectName(QStringLiteral("btnApply"));

        horizontalLayout_2->addWidget(btnApply);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(AppSettingsDialog);

        QMetaObject::connectSlotsByName(AppSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *AppSettingsDialog)
    {
        AppSettingsDialog->setWindowTitle(QApplication::translate("AppSettingsDialog", "Application Settings", 0));
        btnOk->setText(QApplication::translate("AppSettingsDialog", "OK", 0));
        btnCancel->setText(QApplication::translate("AppSettingsDialog", "Cancel", 0));
        btnApply->setText(QApplication::translate("AppSettingsDialog", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class AppSettingsDialog: public Ui_AppSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPSETTINGSDIALOG_H
