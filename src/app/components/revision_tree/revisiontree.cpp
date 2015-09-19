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
    qDebug("initializing RevisionTree");
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
    ui->revisionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->revisionTableView->horizontalHeader()->setStretchLastSection(true);

    ui->revisionTreeWidget->setRowHeight(mRowHeight);
}

RevisionTree::~RevisionTree()
{
    delete ui;
}

/*!
 * \brief RevisionTree::read
 */
void RevisionTree::read()
{
    ui->revisionTreeWidget->resetGraph();
    clearGraph();
    resize(width(),ui->revisionTreeWidget->height());

    int rowNum = ui->revisionTableView->model()->rowCount();
    for(int i = 0; i < rowNum; ++i)
    {
        ui->revisionTableView->setRowHeight(i, rowHeight());
    }
}

/*!
 * \brief RevisionTree::clearGraph Clears graph.
 */
void RevisionTree::clearGraph()
{
}

/*!
 * \brief RevisionTree::rowHeight Returns height of single row.
 * \return Height of row.
 */
int RevisionTree::rowHeight() const
{
    return mRowHeight;
}

/*!
 * \brief RevisionTree::setRowHeight Sets new height of row.
 * \param rowHeight New height of row.
 */
void RevisionTree::setRowHeight(int rowHeight)
{
    mRowHeight = rowHeight;
}

/*!
 * \brief RevisionModel::addNode Add new node (vertex to graph), call for each parent if node has many parents (e.g. merge)
 * \param pParentID ID of parent, may be empty if node nas no parent (e.g. initial commit or filtered data)
 * \param pNodeInfo Info about new node
 */
void RevisionTree::addNode(const std::string &pParentID, const std::string &pNodeId)
{
    mModel->addNode(pParentID, pNodeId);
}

/*!
 * \brief RevisionModel::putProperty Adds property for revision item.
 * \param pRecepientId Revision item ID.
 * \param property Property name.
 * \param value Property value for revision item.
 */
void RevisionTree::putProperty(const std::string &pRecepientId, const std::string &property, const QVariant &value)
{
    mModel->putProperty(pRecepientId,property,value);
}

/*!
 * \brief RevisionTree::slotGraphScrollChanged Changes value of vertical scroll
 *  bar of table view, according to pValue.
 * \param pValue New value for vertical scroll bar of table view.
 */
void RevisionTree::slotGraphScrollChanged(int pValue)
{
    disconnect(ui->revisionTableView->verticalScrollBar(),&QScrollBar::valueChanged,
               this,&RevisionTree::slotTableScrollChanged);
    ui->revisionTableView->verticalScrollBar()->setValue(pValue);
    connect(ui->revisionTableView->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotTableScrollChanged,Qt::UniqueConnection);
}

/*!
 * \brief RevisionTree::slotTableScrollChanged Changes value of vertical scroll
 * bar of revision tree widget, according to pValue.
 * \param pValue New value for vertical scroll bar of revision tree widget.
 */
void RevisionTree::slotTableScrollChanged(int pValue)
{
    disconnect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,
               this,&RevisionTree::slotGraphScrollChanged);
    ui->scrollArea->verticalScrollBar()->setValue(pValue);
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,
            this,&RevisionTree::slotGraphScrollChanged,Qt::UniqueConnection);
}
