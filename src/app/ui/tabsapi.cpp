#include "tabsapi.h"
#include "customtabbar.h"

TabsAPI::TabsAPI(QObject *parent):
    QObject(parent)
{

}

int TabsAPI::getCurrentIndex(CustomTabBar *pTabBar)
{    
    return pTabBar->currentIndex();
}

int TabsAPI::getCountTabs(CustomTabBar *pTabBar)
{
    return pTabBar->count();
}

QWidget* getCurrentWidget(CustomTabBar *pTabBar)
{
    return pTabBar->currentWidget();
}

QWidget* getWidget(CustomTabBar *pTabBar, int pIndex)
{
    return pTabBar->widget(pIndex);
}

void TabsAPI::slotAddNewWorkplace(CustomTabBar *pTabBar, const QString &pName)
{
    pTabBar->slotAddNewWorkplace(pName);
}
