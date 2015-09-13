#ifndef SLAPIFACTORY_H
#define SLAPIFACTORY_H

class Aggregator;
class QObject;

class SLAPIFactory
{
public:
    static Aggregator *create(QObject *parent = nullptr);
};

#endif // SLAPIFACTORY_H
