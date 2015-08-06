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
#include <iostream>
#include <boost/graph/topological_sort.hpp>

RevisionTree::RevisionTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RevisionTree)
{
    ui->setupUi(this);
}

RevisionTree::~RevisionTree()
{
    delete ui;
}

void RevisionTree::setGraph(const revision_graph &pGraph)
{
    ui->revisionTreeWidget->setGraph(pGraph);
    mGraph = pGraph;
    clearScene();
    read();
}

void RevisionTree::clearScene()
{
}

void RevisionTree::read()
{
}
