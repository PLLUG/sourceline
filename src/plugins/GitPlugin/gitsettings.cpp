#include "gitsettings.h"

GitSetting::GitSetting(Settings *pSettings, QWidget *parent) :
    SettingsPage(pSettings, parent)
{
    QVBoxLayout *lLayout = new QVBoxLayout;
    setLayout(lLayout);

    QCheckBox *lCheckBox = new QCheckBox("auto");
    lLayout->addWidget(lCheckBox);

    QComboBox *lComboBox = new QComboBox();
    QStringList str;
    str << "text1" << "text2" << "text3";
    lComboBox->addItems(str);
    lLayout->addWidget(lComboBox);

    settings()->add("auto", lCheckBox, "checked");
    settings()->subscribe("auto", this, SLOT(slotSmthChanged(QVariant)));
    settings()->add("combo", lComboBox, "currentText");
    settings()->subscribe("combo", this, SLOT(slotComboChanged(QVariant)));

    setName("GitPlugin");
    setIcon(QIcon(":/splash/img/sourceline.ico"));
    settings()->setSettingsPath("git_plugin/group1");
}

void GitSetting::slotSmthChanged(QVariant pValue)
{
    qDebug() << "inside plugin : smth changed = " << pValue.toBool();
}

void GitSetting::slotComboChanged(QVariant pValue)
{
    qDebug() << "inside plugin : combo changed = " << pValue.toString();
}

