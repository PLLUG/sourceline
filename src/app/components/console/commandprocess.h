#ifndef COMMANDPROCESS_H
#define COMMANDPROCESS_H

#include <QObject>

class QProcess;

/*!
 * \brief The CommandProcess class is responsible for execution of commands as a separate
 * processes.
 */
class CommandProcess : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcess(QObject *parent = 0);

signals:
    void standardOutput(QString text);
    void errorOutput(QString text);
    void started();
    void finished();

public slots:
    void execute(QString command, QStringList parameters);

private slots:
    void readStandardOutput();
    void readStandardError();

private:
    QProcess *mProcess;
};

#endif // COMMANDPROCESS_H
