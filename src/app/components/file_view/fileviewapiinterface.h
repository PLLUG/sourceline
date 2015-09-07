#ifndef PUBLICFILEVIEWAPI_H
#define PUBLICFILEVIEWAPI_H

#include "ifileviewapi.h"
#include <QVariant>

class InvocationBased;
class FileViewAPI;

class PublicFileViewAPI : public IFileViewAPI
{
    Q_OBJECT
public:
    explicit PublicFileViewAPI(QObject *parent = 0) :
        IFileViewAPI(parent) {}

signals:
    void invokeCommand(QByteArray pSignature, QVariant);

public slots:
    void addToMenu(QString commandId) final
    {
        emit invokeCommand("addToMenu(QString)", commandId);
    }

};

#endif // PUBLICFILEVIEWAPI_H
