#include "tabsapi.h"
#include "customtabbar.h"

TabsAPI::TabsAPI(QObject *parent):
    QObject(parent)
{

}

int TabsAPI::getCurrentIndex(CustomTabBar *pTabBar) const
{    
    return pTabBar->currentIndex();
}

int TabsAPI::getCountTabs(CustomTabBar *pTabBar) const
{
    return pTabBar->count();
}

QWidget* TabsAPI::getCurrentWidget(CustomTabBar *pTabBar) const
{
    return pTabBar->currentWidget();
}

QWidget* TabsAPI::getWidget(CustomTabBar *pTabBar, int pIndex) const
{
    return pTabBar->widget(pIndex);
}

void TabsAPI::slotAddNewWorkplace(CustomTabBar *pTabBar, const QString &pName)
{
    pTabBar->slotAddNewWorkplace(pName);
}
