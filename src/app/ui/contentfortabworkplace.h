#ifndef CONTENTFORTABWORKPLACE_H
#define CONTENTFORTABWORKPLACE_H

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
