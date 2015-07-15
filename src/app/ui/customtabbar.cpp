/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Mykola Molochiy (molochiy@gmail.com)                          ***
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

#include "customtabbar.h"
#include "ui_customtabbar.h"
#include "contentfortabworkplace.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CustomTabBar)
{
    ui->setupUi(this);
    this->setTabsClosable(true);
    this->setMovable(true);    
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseWorkplace(int)));
}

CustomTabBar::~CustomTabBar()
{
    delete ui;
}

void CustomTabBar::slotAddNewWorkplace(const QString &pName)
{
    QTabWidget::addTab(new ContentForTabWorkplace(this), pName);
    setCurrentIndex(this->count()-1);
}

void CustomTabBar::slotCloseWorkplace(int pIndex)
{
    removeTab(pIndex);
}

