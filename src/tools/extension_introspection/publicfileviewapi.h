#ifndef PUBLICFILEVIEWAPI_H
#define PUBLICFILEVIEWAPI_H

#include <QObject>
#include <QVariant>

class InvocationBased;
class FileViewAPI;

class PublicFileViewAPI : public QObject
{
    Q_OBJECT
public:
    explicit PublicFileViewAPI(QObject *parent = 0);

signals:
    void invokeCommand(QByteArray pSignature, QVariant);

public slots:
    void addToMenu(QString commandId);
};

#endif // PUBLICFILEVIEWAPI_H
