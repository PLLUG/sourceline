#include "texteditinterface.h"

#include "string.h"
#include <QMetaClassInfo>

const QByteArray SHOW_CLIENT_EXPLORER_CALL("appendPlainText(QString)");

TextEditInterface::TextEditInterface(QObject *parent) : QObject(parent)
{
    initInterface();
}

void TextEditInterface::setText(QString text)
{
    qDebug(qPrintable(text));
    qDebug(qPrintable(mInterfafceId));
    emit invoked(mInterfafceId, SHOW_CLIENT_EXPLORER_CALL, text, QVariant(), QVariant(), QVariant(), QVariant());
}

void TextEditInterface::initInterface()
{
    const QMetaObject *metaObj = metaObject();
    for (int index = 0; index < metaObj->classInfoCount(); ++index)
    {
        QMetaClassInfo classInfoItem = metaObj->classInfo(index);

        if (0 == strcmp(classInfoItem.name(), "SlInterfaceId"))
        {
            mInterfafceId = classInfoItem.value();
            break;
        }
    }
}

