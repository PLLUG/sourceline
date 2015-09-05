#include "sourcelineclient.h"

/*!
 * \brief Public constructor.
 * \param connectionId Client connection id.
 * \param parent Pointer to parent object.
 */
SourceLineClient::SourceLineClient(const QString &connectionId, QObject *parent) :
    QObject(parent)
  , mConnectionId{connectionId}
{

}

/*!
 * \brief Begin process of client initialization and starting.
 */
void SourceLineClient::start()
{
    // Connection code here...
}

