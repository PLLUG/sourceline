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
    if(mPageHash.isEmpty())
    {
    mPageHash.insert(mPageHash.count(), mPageHash.count());
    }
    else
    {

        QList<int> lKeys = mPageHash.keys();
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
        mPageHash.insert(id, mPageHash.count());

    }
    return mPageHash.value(mPageHash.count());

}

int PageManager::getPageID(int index)
{
    //TASK: fixme
    return mPageHash.key(index, -1);
//    for(QMap<int,int>::iterator iter = mPageHash.begin(); iter!=mPageHash.end(); iter++)
//        if(iter.value() == index)
//           return iter.key();
}

int PageManager::getActiveIndex()
{

    return mPageHash.count();

}

void PageManager::slotAddPage(QString lName)
{
    emit pageAdded(getPageID(), lName);
}

void PageManager::slotRemovePage(int index)
{
    QMap<int,int>::iterator iter=mPageHash.begin();
    for(; iter!=mPageHash.end(); iter++)
    {
        if(iter.value() == index)
            break;
    }

    for(QMap<int,int>::iterator iter = mPageHash.begin(); iter!=mPageHash.end(); iter++)
    {
        if(iter.value() > index)
            iter.value()--;
    }

    qDebug()<<"iter key "<<iter.key();
    mPageHash.remove(iter.key());
}

void PageManager::slotTabMoved(int from, int to)
{
    int lFrom = 0, lTo = 0;
    for(QMap<int,int>::iterator iter = mPageHash.begin(); iter!=mPageHash.end(); iter++)
        if(iter.value() == from)
            lFrom = iter.key();
        else if(iter.value() == to)
            lTo = iter.key();

    int a = 0;
    a = mPageHash[lFrom];
    mPageHash[lFrom] = mPageHash[lTo];
    mPageHash[lTo] = a;
}
