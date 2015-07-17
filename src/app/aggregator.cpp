#include "aggregator.h"

Aggregator::Aggregator(QObject *parent): QObject(parent)
{  
}

Aggregator::~Aggregator()
{
}

/*!
 * \brief Set obj as children of Aggregator class.
 */
void Aggregator::addObject(QObject *obj)
{
    obj->setParent(this);
}