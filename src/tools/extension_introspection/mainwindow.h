#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FileViewAPI;
class CommandManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    FileViewAPI *api() const;
    CommandManager *commandManager() const;

private:
    Ui::MainWindow *ui;
    FileViewAPI *mApi;
    CommandManager *mCommandManager;
};

#endif // MAINWINDOW_H
