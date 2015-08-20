/********************************************************************************
** Form generated from reading UI file 'revisionview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVISIONVIEW_H
#define UI_REVISIONVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RevisionView
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *RevisionView)
    {
        if (RevisionView->objectName().isEmpty())
            RevisionView->setObjectName(QStringLiteral("RevisionView"));
        RevisionView->resize(400, 300);
        gridLayout = new QGridLayout(RevisionView);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(RevisionView);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(RevisionView);

        QMetaObject::connectSlotsByName(RevisionView);
    } // setupUi

    void retranslateUi(QWidget *RevisionView)
    {
        RevisionView->setWindowTitle(QApplication::translate("RevisionView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class RevisionView: public Ui_RevisionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVISIONVIEW_H
