#ifndef CONTENTFORTAB_H
#define CONTENTFORTAB_H

#include <QMainWindow>
#include <QSettings>

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
    explicit ContentForTab(QWidget *parent = 0, QString TabName = QString());
    ~ContentForTab();

    QByteArray tabState() const;
    bool isContentVisible();
    void setVisibleForContent(bool pVisible);

public slots:
    void setTabState(QVariant pTabState);
    void sentSignalTabStateChanged();

private:
    void closeEvent(QCloseEvent *pEvent);

signals:
    void tabStateChanged(QByteArray pTabState);

private:
    Ui::ContentForTab *ui;

    RevisionTreeDock *mHistoryTree;
    RevisionTree *mRevisionTreeContents;
    EditorView *mEditorView;
    DockFileView *mFileView;
    FileView *mFileViewContents;
    DockConsole *mConsole;
    ConsoleView *mConsoleContents;
    bool mIsVisble;
    QString mPathToSettingsFile;
    QSettings *mSettings;
};

#endif // CONTENTFORTAB_H
