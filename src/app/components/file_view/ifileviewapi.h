#ifndef IFILEVIEWAPI
#define IFILEVIEWAPI

#include <QObject>
#include <QString>
#include "apibase.h"

class IFileViewAPI : public ApiBase
{
    Q_OBJECT
public:
    IFileViewAPI(QObject *parent) : ApiBase(parent) {}

public slots:
    virtual void addToMenu(QString commandId) = 0;
};

#endif // IFILEVIEWAPI

