#ifndef EXAMPLECOMPONENT_H
#define EXAMPLECOMPONENT_H

#include "ui/genericcomponent.h"

class ExampleComponent : public GenericComponent
{
    Q_OBJECT
public:
    explicit ExampleComponent(QWidget *parent = 0);

    virtual QString name() const;

signals:

public slots:
};

#endif // EXAMPLECOMPONENT_H
