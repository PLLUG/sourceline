#include "aggregator.h"
#include "pluginapi.h"
#include "testcommand.h"


Aggregator::Aggregator(QObject *parent): QObject(parent)
{
    mPluginAPI = new PluginAPI();
}

Aggregator::~Aggregator()
{
}

/*!
 * \brief Set obj as children of Aggregator class.
 */
void Aggregator::addObject(QObject *pObj)
{
    pObj->setParent(this);
}

void Aggregator::registerCommand(TestCommand *pCommand)
{
    mPluginAPI->slotRegisterCommand(pCommand);
}
