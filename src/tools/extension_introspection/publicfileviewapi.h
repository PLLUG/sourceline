#ifndef PUBLICFILEVIEWAPI_H
#define PUBLICFILEVIEWAPI_H

#include <QObject>

class InvocationBased;
class FileViewAPI;

class PublicFileViewAPI : public QObject
{
    Q_OBJECT
public:
    explicit PublicFileViewAPI(QObject *parent = 0);

signals:
    void invokeCommand(QByteArray pSignature);

public slots:
};

#endif // PUBLICFILEVIEWAPI_H
