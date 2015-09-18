#ifndef GENERICCOMPONENT_H
#define GENERICCOMPONENT_H

#include <QWidget>

class GenericComponent : public QWidget
{
    Q_OBJECT
public:
    explicit GenericComponent(QWidget *parent = 0);

    /*!
     * \brief Used to mention component in dock title, in menus, settings etc..
     * \return Short unique but human readable name for component.
     */
    virtual QString name() const = 0;

signals:

public slots:
};

#endif // GENERICCOMPONENT_H
