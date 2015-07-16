#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <QObject>
#include <iterator>
#include <QtAlgorithms>
#include "pluginsupport/componentsorter.h"

class Aggregator: public QObject
{
    Q_OBJECT

public:
    Aggregator(QObject *obj = nullptr);
    ~Aggregator();
    void setObject(QObject *obj);

    template <typename T>
    T* object();
};

template <typename T>
T* Aggregator::object()
{
    QObjectList childrens = this->children();
    for(int i = 0; i < childrens.count(); i++)
    {
        T *ob = qobject_cast<T*>(childrens[i]);
        if(T *ob = qobject_cast<T*>(childrens[i]))
        {
            return ob;
        }
        else
        {
            return nullptr;
        }
    }
}

#endif // AGGREGATOR_H
