#ifndef CONTENTFORTABWORKPLACE_H
#define CONTENTFORTABWORKPLACE_H

#include <QMainWindow>
#include "ui/consoleview.h"
#include "ui/dockconsole.h"
#include "ui/dockfileview.h"
#include "ui/editorview.h"
#include "ui/fileview.h"
#include "ui/historytree.h"
#include "ui/revisiontable.h"
#include "ui/revisionview.h"

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
