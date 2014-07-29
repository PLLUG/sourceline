#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include "guidefs.h"

class ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject *parent = 0);

signals:

public slots:

};

#endif // ACTIONMANAGER_H
