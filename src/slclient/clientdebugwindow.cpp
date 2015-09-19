#include "clientdebugwindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QBuffer>
#include <QTimer>
#include <QDebug>

QByteArray ClientDebugWindow::mBuffer = QByteArray();

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString messageType;

    switch (type) {
    case QtDebugMsg:
        messageType = "D";
        break;
    case QtInfoMsg:
        messageType = "I";
        break;
    case QtWarningMsg:
        messageType = "W";
        break;
    case QtCriticalMsg:
        messageType = "C";
        break;
    case QtFatalMsg:
        abort();
    }

    QString formatedMessage = QString("[%1 %2:%3] : %4\n\n")
            .arg(messageType, context.function, QString::number(context.line), msg);

    QByteArray localMsg = formatedMessage.toLocal8Bit();
    fprintf(stderr, localMsg.constData());
    ClientDebugWindow::writeMessage(localMsg);
}

static const int UPDATE_LOG_INTERVAL(1000 * 2); // Every 2 sec.

/*!
 * \brief Public constructor.
 * \param parent Pointer to parent object.
 */
ClientDebugWindow::ClientDebugWindow(QWidget *parent) :
    QWidget(parent)
  , mLogTextEdit{new QPlainTextEdit()}
  , mUpdateLogTimer(new QTimer())
{
    // Custom handler that will be write to stderr and QBuffer
    qInstallMessageHandler(myMessageOutput);

    connect(mUpdateLogTimer, &QTimer::timeout, this, &ClientDebugWindow::updateLog, Qt::UniqueConnection);
    mUpdateLogTimer->start(UPDATE_LOG_INTERVAL);

    // Window UI
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mLogTextEdit);
    setLayout(mainLayout);

    resize(800, 400);
}

void ClientDebugWindow::writeMessage(const QByteArray &msg)
{
    mBuffer.append(msg);
}

/*!
 * \brief Get all recent log messages from log buffer and append to the end of text output
 * on log window.
 */
void ClientDebugWindow::updateLog()
{
    if (!mBuffer.isEmpty())
    {
        mLogTextEdit->appendPlainText(mBuffer);
        mBuffer.clear();
    }
}

