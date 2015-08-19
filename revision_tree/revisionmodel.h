#ifndef REVISIONMODEL_H
#define REVISIONMODEL_H
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
#include <QAbstractTableModel>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <set>
#include <map>
#include "revisionnode.h"

using revision_graph = boost::adjacency_list<
boost::listS,
boost::vecS,
boost::bidirectionalS, // bidirectional because we want to show lists of parents and children of nodes
RevisionNode>;
using vertex = boost::graph_traits<revision_graph>::vertex_descriptor;

class RevisionModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RevisionModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    revision_graph graph() const;
    void debugTree(const revision_graph &graph) const;
    void addNode(const std::string &pParentID, const RevisionNode &pNodeInfo);
    void setInitialNode(const RevisionNode &);

    void putProperty(const std::string &pRecepientId, const std::string &property, const QVariant &value);

private:
    vertex vertexAt(int row) const;

private:
    revision_graph mGraph;
    std::map<std::string, std::map<std::string,QVariant>> mPropertyMaps;//property maps by property name
    boost::dynamic_properties mProperties;
    std::vector< vertex > sorted_vertices;
};

#endif // REVISIONMODEL_H
