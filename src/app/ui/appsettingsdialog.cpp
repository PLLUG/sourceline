/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"

AppSettingsDialog::AppSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);
    settingsChanged = false;
    ui->btnApply->setEnabled(settingsChanged);;
    connect(ui->btnOk, SIGNAL(clicked()), SLOT(slotBtnOk()));
    connect(ui->btnCancel, SIGNAL(clicked()), SLOT(slotBtnCancel()));
    connect(ui->btnApply, SIGNAL(clicked()), SLOT(slotBtnApply()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), SLOT(slotOnListItemClicked(int)));
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}

void AppSettingsDialog::addSettingsItem(SettingsPage *pSettingPage)
{
    qDebug() << "Added settings item!";
    mSPages.append(pSettingPage);
    settingsNameList.append(pSettingPage->name());
    QListWidgetItem* lwi = new QListWidgetItem(pSettingPage->icon(), pSettingPage->name());
    lwi->setSizeHint(QSize(0, 40));
    ui->listWidget->addItem(lwi);
    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->addWidget(pSettingPage);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->btnOk, SIGNAL(clicked(bool)),
            this, SLOT(slotBtnOk()), Qt::UniqueConnection);
    connect(ui->btnCancel, SIGNAL(clicked(bool)),
            pSettingPage, SLOT(slotCancel()), Qt::UniqueConnection);
    connect(pSettingPage, SIGNAL(signalSettingsStateChanged()),
            this, SLOT(slotSettingsChanged()), Qt::UniqueConnection);
}

void AppSettingsDialog::slotBtnOk()
{
    qDebug() << "btnOk pressed!";
    slotBtnApply();
    this->close();
}

void AppSettingsDialog::slotBtnCancel()
{
    qDebug() << "btnCancel pressed!";
    mSPages.at(ui->stackedWidget->currentIndex())->settings()->revert();
    settingsChanged = false;
    ui->btnApply->setEnabled(settingsChanged);
    this->close();
}

void AppSettingsDialog::slotBtnApply()
{
    qDebug() << "btnApply pressed!";
    mSPages.at(ui->stackedWidget->currentIndex())->settings()->commit();
    settingsChanged = false;
    ui->btnApply->setEnabled(settingsChanged);
}

void AppSettingsDialog::slotSettingsChanged()
{
    qDebug() << "Settings changed";
    settingsChanged = true;
    ui->btnApply->setEnabled(settingsChanged);
}

void AppSettingsDialog::slotOnListItemClicked(int index)
{
    qDebug() << "On item click" << index;
    ui->stackedWidget->setCurrentIndex(index);
    emit signalSettingPageChanged(settingsNameList.at(index));
}

void AppSettingsDialog::readSettings()
{
    qDebug() << "Read settings";
    emit signalReadSetting();
}

void AppSettingsDialog::writeSettings()
{
    qDebug() << "Write settings";
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        emit signalSettingPageChanged(settingsNameList.at(i));
        emit signalWriteSetting();
    }
}
