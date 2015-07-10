#ifndef CONTENTFORTABWORKPLACE_H
#define CONTENTFORTABWORKPLACE_H

#include <QWidget>
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

    HistoryTree *uiHistoryTree;
    RevisionView *dockWidgetContents_5;

    EditorView *uiEditorView;
    QWidget *dockWidgetContents;
    FileView *dockWidgetContents_4;
    DockFileView *uiFileView;
    RevisionTable *uiRevisionTable;
    QWidget *dockWidgetContents_8;
    DockConsole *uiConsole;
    ConsoleView *dockWidgetContents_3;

private:
    Ui::ContentForTabWorkplace *ui;
};

#endif // CONTENTFORTABWORKPLACE_H
