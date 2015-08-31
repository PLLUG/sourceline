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
void Aggregator::addObject(QObject *pObj)
{
    if (!mContents.contains(pObj))
    {
        mContents.append(pObj);
    }
}
