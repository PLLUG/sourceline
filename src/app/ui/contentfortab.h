#ifndef CONTENTFORTAB_H
#define CONTENTFORTAB_H

#include <QMainWindow>

class RevisionTreeDock;
class EditorView;
class FileView;
class DockFileView;
class DockConsole;
class ConsoleView;
class RevisionTree;

namespace Ui {
class ContentForTab;
}

class ContentForTab : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContentForTab(QWidget *parent = 0);
    ~ContentForTab();

private:
    Ui::ContentForTab *ui;

    RevisionTreeDock *mHistoryTree;
    RevisionTree *mRevisionTreeContents;
    EditorView *mEditorView;
    DockFileView *mFileView;
    FileView *mFileViewContents;
    DockConsole *mConsole;
    ConsoleView *mConsoleContents;
};

#endif // CONTENTFORTAB_H
