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

    HistoryTree *uiHistoryTree;
    RevisionView *uiHistoryTreeContents;
    EditorView *uiEditorView;
    FileView *uiFileViewContents;
    DockFileView *uiFileView;
    RevisionTable *uiRevisionTable;
    DockConsole *uiConsole;
    ConsoleView *uiConsoleContents;
};

#endif // CONTENTFORTAB_H
