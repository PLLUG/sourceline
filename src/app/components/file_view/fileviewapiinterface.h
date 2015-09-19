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
    void invokeCommand(QByteArray pSignature, QVariant, QVariant, QVariant, QVariant, QVariant);

public slots:
    void addToMenu(QString commandId) override final
    {
        emit invokeCommand("addToMenu(QString)", commandId, QVariant(), QVariant(), QVariant(), QVariant());
    }

};

#endif // PUBLICFILEVIEWAPI_H
