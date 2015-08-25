#ifndef TESTINERFACE_H
#define TESTINERFACE_H

#include <QObject>
class QPlainTextEdit;

class TestInerface : public QObject
{
    Q_OBJECT
public:
    explicit TestInerface(QPlainTextEdit *textEdit, QObject *parent = 0);

signals:

public slots:
    Q_REVISION(1) void setText(QString text);
    Q_REVISION(1) int testReturn(QString test);

private:
    QPlainTextEdit *mTextEdit;
};

#endif // TESTINERFACE_H
