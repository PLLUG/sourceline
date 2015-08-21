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

#include <QPushButton>
#include <QDebug>

AppSettingsDialog::AppSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(slotBtnOk()));
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(slotBtnCancel()));
    mApplyButton = ui->buttonBox->button(QDialogButtonBox::Apply);
    connect(mApplyButton, SIGNAL(clicked()), SLOT(slotBtnApply()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), SLOT(slotOnListItemClicked(int)));
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}

void AppSettingsDialog::addSettingsItem(SettingsPage *pSettingPage)
{
    if (!pSettingPage)
    {
        qDebug("AppSettingsDialog::addSettingsItem: settings page is 0");
        return;
    }

    mSettingPages.append(pSettingPage);
    mSettingsNameList.append(pSettingPage->name());

    QListWidgetItem* lListWidgetItem = new QListWidgetItem(pSettingPage->icon(), pSettingPage->name());
    lListWidgetItem->setSizeHint(QSize(0, 40));
    ui->listWidget->addItem(lListWidgetItem);
    ui->listWidget->setCurrentRow(0);

    ui->stackedWidget->addWidget(pSettingPage);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(slotBtnOk()));
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(slotBtnCancel()));
    connect(pSettingPage->settings(), SIGNAL(modified(bool)),
        this, SLOT(slotPageModified()), Qt::UniqueConnection);
}

void AppSettingsDialog::slotBtnOk()
{
    slotBtnApply();
    this->close();
}

void AppSettingsDialog::slotBtnCancel()
{
    mSettingPages.at(ui->stackedWidget->currentIndex())->settings()->revert();
    this->close();
}

void AppSettingsDialog::slotBtnApply()
{
    mSettingPages.at(ui->stackedWidget->currentIndex())->settings()->commit();
}

void AppSettingsDialog::slotOnListItemClicked(int pIndex)
{
    ui->stackedWidget->setCurrentIndex(pIndex);
}

void AppSettingsDialog::slotPageModified()
{
    bool isModified = false;

    foreach (SettingsPage *lSettingsPage, mSettingPages)
    {
        if (lSettingsPage && lSettingsPage->settings())
        {
            isModified |= lSettingsPage->settings()->isModified();
        }
    }

    mApplyButton->setEnabled(isModified);
}
