#include "aggregator.h"

Aggregator::Aggregator(QObject *obj)
{
    obj->setParent(this);
}

Aggregator::~Aggregator()
{
}

/*!
 * \brief Set obj as children of Aggregator class.
 */
void Aggregator::setObject(QObject *obj)
{
    obj->setParent(this);
}
