#ifndef GITSETTINGS_H
#define GITSETTINGS_H

#include "settingspage.h"
#include "settings.h"
#include <QVariant>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>

#include <QDebug>

class GitSetting : public SettingsPage
{
    Q_OBJECT
public:
    explicit GitSetting(Settings *pSettings, QWidget *parent = 0);

signals:
    void signalGetSettings(QString pPath);

public slots:
    void slotSmthChanged(QVariant pValue);
    void slotComboChanged(QVariant pValue);
};


#endif // GITSETTINGS_H
