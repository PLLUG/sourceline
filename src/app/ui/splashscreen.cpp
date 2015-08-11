#include "splashscreen.h"

#include <QPainter>
#include <QPaintEvent>

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    mPercentage = 0;
    mStartWidth = 0;
    mEndWidth = 0;
}

void SplashScreen::setSplashScreen(const QPixmap &pSplash)
{
    mSplash = pSplash;
    setFixedSize(mSplash.size());
}

void SplashScreen::setLoadLayer(const QPixmap &pLoad, int pStartWidth, int pEndWidth)
{
    mLoad = pLoad;
    mStartWidth = pStartWidth;
    mEndWidth = pEndWidth;
}

void SplashScreen::slotSetPercentage(int pPercentage)
{
    mPercentage = pPercentage;
    repaint();
}

void SplashScreen::paintEvent(QPaintEvent *e)
{
    QPainter lPainter(this);
    lPainter.drawPixmap(e->rect(), mSplash, e->rect());

    int lWidth = mStartWidth + (mEndWidth - mStartWidth) * mPercentage * 0.01;

    QRect lAvailRect(0, 0, lWidth, geometry().height());

    QRect lDrawingRect = e->rect().intersected(lAvailRect);

    lPainter.drawPixmap(lDrawingRect, mLoad, lDrawingRect);
}
