#ifndef FILEVIEWAPI_H
#define FILEVIEWAPI_H

#include "ifileviewapi.h"

#include <QString>

class CommandManager;
class FileView;

class FileViewAPI : public IFileViewAPI
{
    Q_OBJECT
public:
    explicit FileViewAPI(FileView &fileView, CommandManager &commandManager, QObject *parent = 0);

public slots:
    void addToMenu(QString pCommandID) final;

private:
    FileView &mFileView;
    CommandManager &mCommandManager;
};

#endif // FILEVIEWAPI_H
