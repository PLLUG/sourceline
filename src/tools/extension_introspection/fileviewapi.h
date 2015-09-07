#ifndef FILEVIEWAPI_H
#define FILEVIEWAPI_H

#include <QObject>
#include <QString>

class CommandManager;
class FileView;

class FileViewAPI : public QObject
{
    Q_OBJECT
public:
    explicit FileViewAPI(QObject *parent = 0);

    void setCommandManeger(CommandManager *pCommandManager);

    void setFileView(FileView *pFileView);

signals:

public slots:
    void addToMenu(QString pCommandID);

private:
    CommandManager *mCommandManager;
    FileView* mFileView;
};

#endif // FILEVIEWAPI_H
