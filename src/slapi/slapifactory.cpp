#include "slapifactory.h"

#include <QObject>
#include "aggregator.h"

// Here actually goes all API classes that should be instantiated and added to aggregator
#include "fileviewapiinterface.h"

Aggregator *SLAPIFactory::create(QObject *parent)
{
    Aggregator *rAggregator = new Aggregator(parent);
    rAggregator->addObject(new PublicFileViewAPI(parent));
    return rAggregator;
}
