#ifndef TEXTEDITINTERFACE_H
#define TEXTEDITINTERFACE_H

#include <QObject>
#include <QByteArray>
#include <QVariant>

class TextEditInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("SlInterfaceId", "ClientExplorer")
public:
    explicit TextEditInterface(QObject *parent = 0);

signals:
    void invoked(QByteArray, QByteArray, QVariant, QVariant, QVariant, QVariant, QVariant);

public slots:
    void setText(QString text);

private:
    void initInterface();

private:
    QByteArray mInterfafceId;
};

#endif // TEXTEDITINTERFACE_H
