#include "examplecomponent.h"

ExampleComponent::ExampleComponent(QWidget *parent) : QWidget(parent)
{

}

QString ExampleComponent::name() const
{
    return QStringLiteral("Example Component");
}

