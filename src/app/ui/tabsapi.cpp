#include "tabsapi.h"
#include <QDebug>

TabsAPI::TabsAPI(QObject *parent):
    QObject(parent)
{

}

void TabsAPI::slotChangeCurrentTab(int index)
{
    emit currentWorkplaceChanged(getTabID(index));
}

int TabsAPI::getTabID()
{
    if(mTabHash.isEmpty())
    {
        mTabHash.insert(mTabHash.count(), mTabHash.count());
    }
    else
    {
        QList<int> lKeys = mTabHash.keys();
        qSort(lKeys);
        QList<int>::iterator iter = std::max_element(lKeys.begin(),lKeys.end());
        int id = 0;
        bool idSet = false;

        for(int i=0; i < lKeys.first(); i++)
        {
            if(i != lKeys.first())
            {
                id = i;
                idSet = true;
            }
        }

        if(!idSet)
        {
            for(int i = 0; i < lKeys.size()-1; i++)
            {

               if(lKeys[i+1] - lKeys[i] != 1)
               {
                   idSet = true;
                   id = lKeys[i]+1;
               }
            }
        }
        if(!idSet)
        {
            id = *iter+1;
        }
        mTabHash.insert(id, mTabHash.count());
    }
    return mTabHash.value(mTabHash.count());
}

int TabsAPI::getTabID(int index)
{
    return mTabHash.key(index, -1);
}

int TabsAPI::getActiveIndex()
{
    return mTabHash.count();
}

void TabsAPI::slotAddNewWorkplace(QString lName)
{
    emit newWorkplaceAdded(getTabID(), lName);
}

void TabsAPI::slotRemoveWorkplace(int index)
{
    QMap<int,int>::iterator iter=mTabHash.begin();
    for(; iter!=mTabHash.end(); iter++)
    {
        if(iter.value() == index)
            break;
    }

    for(QMap<int,int>::iterator iter = mTabHash.begin(); iter!=mTabHash.end(); iter++)
    {
        if(iter.value() > index)
            iter.value()--;
    }

    qDebug()<<"iter key "<<iter.key();
    mTabHash.remove(iter.key());
}

void TabsAPI::slotTabMoved(int from, int to)
{
    int lFrom = 0, lTo = 0;
    for(QMap<int,int>::iterator iter = mTabHash.begin(); iter!=mTabHash.end(); iter++)
        if(iter.value() == from)
            lFrom = iter.key();
        else if(iter.value() == to)
            lTo = iter.key();

    int a = 0;
    a = mTabHash[lFrom];
    mTabHash[lFrom] = mTabHash[lTo];
    mTabHash[lTo] = a;
}
