#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H

#include <QTabWidget>

class QWidget;

namespace Ui {
class CustomTabBar;
}

class CustomTabBar : public QTabWidget
{
    Q_OBJECT

public:
    explicit CustomTabBar(QWidget *parent = 0);
    ~CustomTabBar();
public slots:
    void slotAddNewWorkplace(int index, QString name);
    void slotCloseTab(int);
private:
    Ui::CustomTabBar *ui;
};

#endif // CUSTOMTABBAR_H
