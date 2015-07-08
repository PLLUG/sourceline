#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class PageManager;
class CustomTabBar;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    CustomTabBar *mTabBar;
    PageManager *mPageManager;

signals:
    void mysignal();

private:
    void resizeEvent(QResizeEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

    void CloseWindow();

    void slotQuit();

    void slotAddPage();
};

#endif // MAINWINDOW_H
