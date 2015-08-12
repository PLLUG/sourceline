#ifndef CONTENTFORTAB_H
#define CONTENTFORTAB_H

#include <QMainWindow>

class HistoryTree;
class RevisionView;
class EditorView;
class FileView;
class DockFileView;
class RevisionTable;
class DockConsole;
class ConsoleView;

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

    HistoryTree *mHistoryTree;
    RevisionView *mHistoryTreeContents;
    EditorView *mEditorView;
    FileView *mFileViewContents;
    DockFileView *mFileView;
    RevisionTable *mRevisionTable;
    DockConsole *mConsole;
    ConsoleView *mConsoleContents;
};

#endif // CONTENTFORTAB_H
