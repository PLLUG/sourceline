#ifndef PUBLICFILEVIEWAPI_H
#define PUBLICFILEVIEWAPI_H

#include <QObject>

class PublicFileViewAPI : public QObject
{
    Q_OBJECT
public:
    explicit PublicFileViewAPI(QObject *parent = 0);

signals:

public slots:
};

#endif // PUBLICFILEVIEWAPI_H
