/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Halyna Butovych (galynabutovych@gmail.com)                    ***
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

#include "revisiontree.h"
#include "ui_revisiontree.h"
#include <QDebug>
#include <QHeaderView>
#include <iostream>
#include <boost/graph/topological_sort.hpp>
#include <algorithm>
#include <QScrollBar>
#include <QScrollArea>

RevisionTree::RevisionTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RevisionTree),
    mRowHeight{30}
{
    ui->setupUi(this);
    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->revisionTableView->horizontalHeader()->setFixedHeight(mRowHeight);

    connect(ui->revisionTableView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(slotScrollChanged(int)));
    connect(this, SIGNAL(scrollChanged(int)), ui->scrollArea->verticalScrollBar(), SLOT(setValue(int)));

    ui->revisionTableView->horizontalHeader()->setSectionsMovable(true);
    ui->revisionTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->revisionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

RevisionTree::~RevisionTree()
{
    delete ui;
}

void RevisionTree::setModel(RevisionModel *model)
{
    ui->revisionTableView->setModel(model);
    ui->revisionTreeWidget->setGraph(model->graph());
    mGraph = model->graph();
    clearScene();
    read();
    resize(width(),ui->revisionTreeWidget->height());

    int rowNum = ui->revisionTableView->model()->rowCount();
    for(int i = 0; i < rowNum; i++)
    {
        ui->revisionTableView->setRowHeight(i, rowHeight());
    }
}

void RevisionTree::clearScene()
{
}

void RevisionTree::read()
{
}
int RevisionTree::rowHeight() const
{
    return mRowHeight;
}

void RevisionTree::setRowHeight(int rowHeight)
{
    mRowHeight = rowHeight;
}

void RevisionTree::slotScrollChanged(int value)
{
    emit scrollChanged(value * rowHeight());
}

