#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include <QObject>

class SplashScreen;

class ApplicationBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationBuilder(QObject *parent = 0);

private slots:
    void slotBuild();

public:
    void initUi();
    void loadPlugins();
    void supplyComponents();

private:
    SplashScreen *mSplashScreen;
};

#endif // APPLICATIONBUILDER_H
