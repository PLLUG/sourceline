#ifndef ICOMMAND
#define ICOMMAND

#include <QObject>

#include "aggregator.h"

class ICommand : public QObject
{
    Q_OBJECT
public:
    ICommand(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ICommand() {}

public:
//    virtual void init(Aggregator *aggregator) = 0;
    virtual void trigger(/*Aggregator *aggregator*/) = 0;
};

#endif // ICOMMAND

