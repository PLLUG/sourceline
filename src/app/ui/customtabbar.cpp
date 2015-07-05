#include "customtabbar.h"
#include "ui_customtabbar.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(QWidget *parent) :
    QTabBar(parent),
    ui(new Ui::CustomTabBar)
{
    ui->setupUi(this);
    this->setTabsClosable(true);
    this->setMovable(true);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));
}

CustomTabBar::~CustomTabBar()
{
    delete ui;
}

void CustomTabBar::slotAddTab(int index, QString name)
{
    Q_UNUSED(index);
    //TASK: check whether everything is  ok with index - it is not set
    QTabBar::addTab(name);
    setCurrentIndex(this->count()-1);
}

void CustomTabBar::slotCloseTab(int index)
{
    removeTab(index);
    setCurrentIndex(index);
}
