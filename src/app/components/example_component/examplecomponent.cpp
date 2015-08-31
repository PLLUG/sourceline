#include "examplecomponent.h"

ExampleComponent::ExampleComponent(QWidget *parent) : GenericComponent(parent)
{

}

QString ExampleComponent::name() const
{
    return QStringLiteral("Example Component");
}

