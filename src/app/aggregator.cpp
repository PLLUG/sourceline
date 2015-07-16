#include "aggregator.h"

Aggregator::Aggregator(QObject *obj)
{
    obj->setParent(this);
}

Aggregator::~Aggregator()
{
}

void Aggregator::setObject(QObject *obj)
{
    obj->setParent(this);
}
