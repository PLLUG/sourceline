#include "customtabbar.h"
#include "ui_customtabbar.h"
#include "contentfortab.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CustomTabBar)
{
    ui->setupUi(this);
    setTabsClosable(true);
    setMovable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &CustomTabBar::tabCloseRequested, this, &CustomTabBar::slotCloseTab);
}

CustomTabBar::~CustomTabBar()
{
    delete ui;
}

void CustomTabBar::slotAddNewWorkplace(const QString &pName)
{
    QTabWidget::addTab(new ContentForTab(this), pName);
}

void CustomTabBar::slotCloseTab(int index)
{
    QWidget *w = widget(index);
    if(w)
        w->deleteLater();
    removeTab(index);
}
