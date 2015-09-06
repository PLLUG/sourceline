/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Halyna Butovych (galynabutovych@gmail.com)                    ***
***            Nazarii Plebanskii (nazar796@gmail.com)                       ***
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
    QWidget(parent)
    ,ui{new Ui::RevisionTree}
    ,mRowHeight{30}
  ,mModel{new RevisionModel{this}}
{
    ui->setupUi(this);

    ui->revisionTableView->setModel(mModel);
    ui->revisionTreeWidget->setModel(mModel);

    ui->revisionTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->revisionTableView->horizontalHeader()->setFixedHeight(mRowHeight);

    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotGraphScrollChanged,Qt::UniqueConnection);
    connect(ui->revisionTableView->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotTableScrollChanged,Qt::UniqueConnection);

    ui->revisionTableView->horizontalHeader()->setSectionsMovable(true);
    ui->revisionTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->revisionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

RevisionTree::~RevisionTree()
{
    delete ui;
}

void RevisionTree::read()
{
    ui->revisionTreeWidget->setGraph(mModel->graph());
    mGraph = mModel->graph();
    clearGraph();
    resize(width(),ui->revisionTreeWidget->height());

    int rowNum = ui->revisionTableView->model()->rowCount();
    for(int i = 0; i < rowNum; i++)
    {
        ui->revisionTableView->setRowHeight(i, rowHeight());
    }
}

void RevisionTree::clearGraph()
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

void RevisionTree::addNode(const std::string &pParentID, const RevisionNode &pNodeInfo)
{
    mModel->addNode(pParentID,pNodeInfo);
}

void RevisionTree::putProperty(const std::string &pRecepientId, const std::string &property, const QVariant &value)
{
    mModel->putProperty(pRecepientId,property,value);
}

void RevisionTree::slotGraphScrollChanged(int value)
{
    disconnect(ui->revisionTableView->verticalScrollBar(),&QScrollBar::valueChanged,
               this,&RevisionTree::slotTableScrollChanged);
    ui->revisionTableView->verticalScrollBar()->setValue(value);
    connect(ui->revisionTableView->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotTableScrollChanged,Qt::UniqueConnection);
}

void RevisionTree::slotTableScrollChanged(int value)
{
    disconnect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,
               this,&RevisionTree::slotGraphScrollChanged);
    ui->scrollArea->verticalScrollBar()->setValue(value);
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotGraphScrollChanged,Qt::UniqueConnection);
}
