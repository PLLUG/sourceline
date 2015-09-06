#ifndef CLIENTDEBUGWINDOW_H
#define CLIENTDEBUGWINDOW_H

#include <QWidget>

class QPlainTextEdit;
class QBuffer;
class QTimer;

class ClientDebugWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ClientDebugWindow(QWidget *parent = 0);

    static void writeMessage(const QByteArray &msg);
signals:

private slots:
    void updateLog();

private:
    QPlainTextEdit *mLogTextEdit;
    QTimer *mUpdateLogTimer;

    static QByteArray mBuffer;
};

#endif // CLIENTDEBUGWINDOW_H
