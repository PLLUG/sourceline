#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

#include <QObject>

class SplashScreen;
class ActionManager;
class MainWindow;
class MainMenuBuilder;
class SettingsManager;

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
    void loadSettings();
    void supplyComponents();
    void createUiActions(MainWindow *pMainWindow);

private:
    MainWindow *mMainWindow;
    SplashScreen *mSplashScreen;
    ActionManager *mActionManager;
    MainMenuBuilder *mMainMenuBuilder;
    SettingsManager *mSettingsManager;
};

#endif // APPLICATIONBUILDER_H
