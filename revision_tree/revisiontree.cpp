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
#include <algorithm>

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

std::vector<vertex> *RevisionTree::getSortedGraphByTime(const revision_graph &graph)
{
    int verticesNumb = num_vertices(graph);
    std::vector< vertex > *rVector = new std::vector< vertex >(verticesNumb);

    // Copying vertices from graph to rVector
    boost::graph_traits< revision_graph >::vertex_iterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi)
    {
        rVector->push_back(*vi);
    }

    // Sorting vertices in rVector
    std::sort(rVector->begin(), rVector->end(),
              [&graph](const vertex &vert1, const vertex &vert2) -> bool
    {
        return graph[vert1].created < graph[vert2].created;
    });

    return rVector;
}

void RevisionTree::clearScene()
{
}

void RevisionTree::read()
{
}
