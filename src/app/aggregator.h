#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <QObject>

class Aggregator: public QObject
{
    Q_OBJECT

public:
    Aggregator(QObject *obj = nullptr);
    ~Aggregator();
    void setObject(QObject *obj);
    QObject *object();

private:
    QObject *mObj;
};

#endif // AGGREGATOR_H
