#ifndef FILEVIEWAPI_H
#define FILEVIEWAPI_H

#include <QObject>
#include <QString>

class CommandManager;

class FileViewAPI : public QObject
{
    Q_OBJECT
public:
    explicit FileViewAPI(QObject *parent = 0);

    void setCommandManeger(CommandManager *pCommandManager);

signals:

public slots:
    void addToMenu(QString pCommandID);

private:
    CommandManager *mCommandManager;
};

#endif // FILEVIEWAPI_H
