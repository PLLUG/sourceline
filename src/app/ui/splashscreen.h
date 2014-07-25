#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>

class SplashScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0);

    void setSplashScreen(const QPixmap &pSplash);
    void setLoadLayer(const QPixmap &pLoad, int pStartWidth, int pEndWidth);

signals:

public slots:
    void slotSetPercentage(int pPercentage);

protected:
    void paintEvent(QPaintEvent *e);

private:
    QPixmap mSplash;
    QPixmap mLoad;
    int mPercentage;
    int mStartWidth;
    int mEndWidth;
};

#endif // SPLASHSCREEN_H
