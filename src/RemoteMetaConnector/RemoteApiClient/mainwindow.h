#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TextEditInterface;
class RemoteApiClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void slotSetText();

private:
    Ui::MainWindow *ui;
    TextEditInterface *mInterface;
    RemoteApiClient *mRemoteClient;
};

#endif // MAINWINDOW_H
