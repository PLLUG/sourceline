#include "customtabbar.h"
#include "ui_customtabbar.h"
#include "contentfortabworkplace.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CustomTabBar)
{
    ui->setupUi(this);
    this->setTabsClosable(true);
    this->setMovable(true);    
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));
}

CustomTabBar::~CustomTabBar()
{
    delete ui;
}

void CustomTabBar::slotAddNewWorkplace(const QString &pName)
{
    QTabWidget::addTab(new ContentForTabWorkplace(this), pName);
}
