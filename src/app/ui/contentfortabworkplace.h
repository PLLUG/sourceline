#ifndef CONTENTFORTABWORKPLACE_H
#define CONTENTFORTABWORKPLACE_H

#include <QMainWindow>

class ConsoleView;
class DockConsole;
class DockFileView;
class EditorView;
class FileView;
class HistoryTree;
class RevisionTable;
class RevisionView;

namespace Ui {
class ContentForTabWorkplace;
}

class ContentForTabWorkplace : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContentForTabWorkplace(QWidget *parent = 0);
    ~ContentForTabWorkplace();



private:
    Ui::ContentForTabWorkplace *ui;

    HistoryTree *uiHistoryTree;
    RevisionView *uiHistoryTreeContents;
    EditorView *uiEditorView;
    FileView *uiFileViewContents;
    DockFileView *uiFileView;
    RevisionTable *uiRevisionTable;
    DockConsole *uiConsole;
    ConsoleView *uiConsoleContents;
};

#endif // CONTENTFORTABWORKPLACE_H
