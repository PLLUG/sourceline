#ifndef TESTINERFACE_H
#define TESTINERFACE_H

#include <QObject>

class QPlainTextEdit;

#ifndef Q_MOC_RUN
#define PUBLIC_API
#endif
const QString PUBLIC_API_TAG_VALUE("PUBLIC_API");

class TestInerface : public QObject
{
    Q_OBJECT
public:
    explicit TestInerface(QPlainTextEdit *textEdit, QObject *parent = 0);

signals:

public slots:
    PUBLIC_API void setText(QString text);

private:
    QPlainTextEdit *mTextEdit;
};

#endif // TESTINERFACE_H
