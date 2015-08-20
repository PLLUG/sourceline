/********************************************************************************
** Form generated from reading UI file 'dialogplugins.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPLUGINS_H
#define UI_DIALOGPLUGINS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogPlugins
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeWidget *pluginsTree;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyAndRestartButton;

    void setupUi(QDialog *DialogPlugins)
    {
        if (DialogPlugins->objectName().isEmpty())
            DialogPlugins->setObjectName(QStringLiteral("DialogPlugins"));
        DialogPlugins->resize(532, 397);
        verticalLayout = new QVBoxLayout(DialogPlugins);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(DialogPlugins);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        label->setFont(font);

        verticalLayout->addWidget(label);

        pluginsTree = new QTreeWidget(DialogPlugins);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        pluginsTree->setHeaderItem(__qtreewidgetitem);
        pluginsTree->setObjectName(QStringLiteral("pluginsTree"));

        verticalLayout->addWidget(pluginsTree);

        checkBox = new QCheckBox(DialogPlugins);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout->addWidget(checkBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        okButton = new QPushButton(DialogPlugins);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(DialogPlugins);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyAndRestartButton = new QPushButton(DialogPlugins);
        applyAndRestartButton->setObjectName(QStringLiteral("applyAndRestartButton"));

        horizontalLayout->addWidget(applyAndRestartButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogPlugins);
        QObject::connect(okButton, SIGNAL(clicked()), DialogPlugins, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogPlugins, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogPlugins);
    } // setupUi

    void retranslateUi(QDialog *DialogPlugins)
    {
        DialogPlugins->setWindowTitle(QApplication::translate("DialogPlugins", "Plugins", 0));
        label->setText(QApplication::translate("DialogPlugins", "All changes will take their place after application restart.\n"
"Press \"Apply & Restart\" to restart application immediately.", 0));
        checkBox->setText(QApplication::translate("DialogPlugins", "Show plugin groups", 0));
        okButton->setText(QApplication::translate("DialogPlugins", "Ok", 0));
        cancelButton->setText(QApplication::translate("DialogPlugins", "Cancel", 0));
        applyAndRestartButton->setText(QApplication::translate("DialogPlugins", "Apply and Restart", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogPlugins: public Ui_DialogPlugins {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPLUGINS_H
