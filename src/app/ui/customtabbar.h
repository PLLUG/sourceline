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
    /*!
     * \brief Add New Workplace in mainwindow
     * \param Name of workplace
     */
    void slotAddNewWorkplace(const QString &pName);
private:
    Ui::CustomTabBar *ui;
};

#endif // CUSTOMTABBAR_H
