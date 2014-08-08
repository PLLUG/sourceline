#include "pagemanager.h"
#include <QDebug>
PageManager::PageManager(QObject *parent):
    QObject(parent)
{

}


void PageManager::slotChangeCurrentPage(int index)
{
    emit currentPageChanged(getPageID(index));
}


int PageManager::getPageID()
{
    if(mPageMap.isEmpty())
    {
    mPageMap.insert(mPageMap.count(), mPageMap.count());
    }
    else
    {

        QList<int> lKeys = mPageMap.keys();
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
        mPageMap.insert(id, mPageMap.count());

    }
    return mPageMap.value(mPageMap.count());

}

int PageManager::getPageID(int index)
{
    for(QMap<int,int>::iterator iter = mPageMap.begin(); iter!=mPageMap.end(); iter++)
        if(iter.value() == index)
           return iter.key();
    return NULL;
}

int PageManager::getActiveIndex()
{

    return mPageMap.count();

}

void PageManager::slotAddPage(QString lName)
{
    emit pageAdded(getPageID(), lName);
}

void PageManager::slotRemovePage(int index)
{
    QMap<int,int>::iterator iter=mPageMap.begin();
    for(; iter!=mPageMap.end(); iter++)
    {
        if(iter.value() == index)
            break;
    }

    for(QMap<int,int>::iterator iter = mPageMap.begin(); iter!=mPageMap.end(); iter++)
    {
        if(iter.value() > index)
            iter.value()--;
    }            

    qDebug()<<"iter key "<<iter.key();
    mPageMap.remove(iter.key());
}

void PageManager::slotTabMoved(int from, int to)
{
    int lFrom = 0, lTo = 0;
    for(QMap<int,int>::iterator iter = mPageMap.begin(); iter!=mPageMap.end(); iter++)
        if(iter.value() == from)
            lFrom = iter.key();
        else if(iter.value() == to)
            lTo = iter.key();

    int a = 0;
    a = mPageMap[lFrom];
    mPageMap[lFrom] = mPageMap[lTo];
    mPageMap[lTo] = a;
}
