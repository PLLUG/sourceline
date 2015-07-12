#include "aggregator.h"

#include <QDebug>

Aggregator::Aggregator(QObject *obj)
{
        QObject *mObj = new QObject;
        mObj = obj;
}

Aggregator::~Aggregator()
{
    delete mObj;
}

void Aggregator::setObject(QObject *obj)
{
    mObj = obj;
}

QObject * Aggregator::object()
{
    if(mObj == nullptr)
        qDebug() << "asd!!!!!!!!!!!!";
    return mObj;
}

