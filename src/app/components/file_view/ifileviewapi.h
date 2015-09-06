#ifndef IFILEVIEWAPI
#define IFILEVIEWAPI

#include <QObject>
#include <QString>

class IFileViewAPI : public QObject
{
    Q_OBJECT
public:
    IFileViewAPI(QObject *parent) : QObject(parent) {}

public slots:
    virtual void addToMenu(QString commandId) = 0;
};

#endif // IFILEVIEWAPI

