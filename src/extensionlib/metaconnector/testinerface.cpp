#include "testinerface.h"

#include <QPlainTextEdit>
#include <QDebug>

TestInerface::TestInerface(QPlainTextEdit *textEdit, QObject *parent)
    : QObject(parent), mTextEdit(textEdit)
{

}

void TestInerface::setText(QString text)
{
    mTextEdit->setPlainText(text);
}

int TestInerface::testReturn(QString test)
{
    qDebug() << "TEST " << test;
    return 123; // just magic
}

