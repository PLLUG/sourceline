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

