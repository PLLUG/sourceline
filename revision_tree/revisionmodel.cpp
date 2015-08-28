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

#include <boost/property_map/dynamic_property_map.hpp>
#include "revisionmodel.h"
#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/topological_sort.hpp>
#include <QColor>

//maybe use labeled_graph where labeles are commit ids (and remove id from property)? - no
//#include <boost/graph/labeled_graph.hpp>
//using labeled_graph = boost::labeled_graph<revision_graph,
//std::string // node ID
//>;

//boost bundled properties
//modified adjacency_list.hpp because of compile error

std::ostream& operator<<(std::ostream& os, const QVariant& pVariant)
{
    return os << pVariant.toString().toStdString();
}

std::istream& operator>>(std::istream& is, const QVariant&) //(not supported)
{
    return is;
}

template<typename Value, typename Key>
Value
get_copied(const std::string& name, const boost::dynamic_properties& dp, const Key& key)
{
    for (boost::dynamic_properties::const_iterator i = dp.lower_bound(name);
         i != dp.end() && i->first == name; ++i) {
        if (i->second->key() == typeid(key))
            return boost::any_cast<Value>(i->second->get(key));
    }

    BOOST_THROW_EXCEPTION(boost::dynamic_get_failure(name));
}

RevisionModel::RevisionModel(QObject *parent):
    QAbstractTableModel(parent)
{
}

/*!
 * \brief RevisionModel::debugTree Represent graph in DOT format and send to cout
 * \param graph Boost graph.
 */
void RevisionModel::debugTree(const revision_graph &graph) const
{
    std::cout << "number of vertices in graph: " << boost::num_vertices(mGraph) << std::endl;
    std::cout << "======== rev tree =========" << std::endl;
    boost::write_graphviz(std::cout, graph);
    std::cout << "======= end rev tree ======" << std::endl;
}

/*!
 * \brief RevisionModel::addNode Add new node (vertex to graph), call for each parent if node has many parents (e.g. merge)
 * \param pParentID ID of parent, may be empty if node nas no parent (e.g. initial commit or filtered data)
 * \param pNodeInfo Info about new node
 */
void RevisionModel::addNode(const std::string &pParentID, const RevisionNode &pNodeInfo)
{
    vertex v_new = boost::graph_traits<revision_graph>::null_vertex();
    vertex v_parent = boost::graph_traits<revision_graph>::null_vertex();
    //find vertexes in graph if they are present
    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
        const auto &name = mGraph[v].name;
        if(pNodeInfo.name == name)
        {
            v_new = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_parent || pParentID.empty())
                break;
        }
        else if(pParentID == name)
        {
            v_parent = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_new)
                break;
        }
    }
    if(boost::graph_traits<revision_graph>::null_vertex() == v_parent)
    {
        // parent not found
        // node has no parent if parent is empty
        if(!pParentID.empty())
        {
            RevisionNode parentNodeInfo;
            parentNodeInfo.name = pParentID;
            v_parent = boost::add_vertex(parentNodeInfo, mGraph);
        }
    }
    if(boost::graph_traits<revision_graph>::null_vertex() == v_new)
    {
        //create if not found
        v_new = boost::add_vertex(pNodeInfo, mGraph);
    }
    else
    {
        // node already in, modify data, because probably it was empty
        mGraph[v_new].created = pNodeInfo.created;
    }
    if(boost::graph_traits<revision_graph>::null_vertex() != v_parent &&
            boost::graph_traits<revision_graph>::null_vertex() != v_new &&
            !boost::edge(v_parent,v_new,mGraph).second // edge doesn't exist
            )
    {
        boost::add_edge(v_parent, v_new, mGraph);
    }
    //TODO: take to account that vertices were already sorted
    //perform topological sort (or some other sort later)
    sorted_vertices.clear();
    topological_sort(mGraph, std::back_inserter(sorted_vertices));
}

/*!
 * \brief RevisionModel::putProperty Adds property for revision item.
 * \param pRecepientId Revision item ID.
 * \param property Property name.
 * \param value Property value for revision item.
 */
void RevisionModel::putProperty(const std::string &pRecepientId, const std::string &property, const QVariant &value)
{
    if(pRecepientId.empty() || property.empty())
        return;
    if(!mPropertyMaps.count(property))
    {
        // if conteiner for property doesn't exist, create one
        std::map<std::string, QVariant> propertyMap;
        mPropertyMaps.insert(std::make_pair(property,std::move(propertyMap)));
        boost::associative_property_map<std::map<std::string, QVariant>>
                associativePropertyMap(mPropertyMaps.at(property));
        mProperties.property(property,associativePropertyMap);
        mPropertyNames.push_back(property);
    }
    put(property,mProperties,pRecepientId,value);
}

/*!
 * \brief RevisionModel::vertexAt Returns vertex at given row according to current sort order.
 * \param row Row.
 * \return Vertex of boost graph.
 */
vertex RevisionModel::vertexAt(int row) const
{
    return sorted_vertices.at(row);
}

/*!
 * \brief RevisionModel::rowCount Returns row count - count of revision items.
 * \return Row count.
 */
int RevisionModel::rowCount(const QModelIndex &) const
{
    return boost::num_vertices(mGraph);
}

/*!
 * \brief RevisionModel::columnCount Returns column count. Columns are default columns (id) and user-defined properties for revision items.
 * \return Column count.
 */
int RevisionModel::columnCount(const QModelIndex &) const
{
    return DefaultColumnsCount + mPropertyMaps.size();
}

/*!
 * \brief RevisionModel::data Returns the data stored under the given role for the item referred to by the index.
 * \param index Index
 * \param role Role
 * \return Data for index and role.
 */
QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    if(Qt::DisplayRole == role || Qt::AccessibleTextRole == role)
    {
        vertex v = vertexAt(index.row());
        if(index.column() < DefaultColumnsCount)
        {
            switch (index.column()) {
            case IdColumn:
                return QString::fromStdString(mGraph[v].name);
                break;
            default:
                break;
            }
        }
        else
        {
            const std::string property = mPropertyNames.at(index.column()-DefaultColumnsCount);
            const std::string &name = mGraph[v].name;
            return get_copied<QVariant>(property, mProperties, name);
        }
    }
    else if (Qt::BackgroundColorRole == role)
    {
        if (index.row() % 2)
            return QColor("#DEE8D0");
        else
            return QColor(Qt::white);
    }
    return QVariant();

}

/*!
 * \brief RevisionModel::headerData Returns the data for the given role and section in the header with the specified orientation.
 * \param section Column number for horizontal headers, row number for vertical headers.
 * \param orientation Horizontal or vertical orientation of header.
 * \param role Role.
 * \return Header data for role and orientation.
 */
QVariant RevisionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant headerName;
    if(Qt::DisplayRole == role || Qt::AccessibleTextRole == role)
    {
        if(Qt::Horizontal == orientation)
        {
            //TODO:choose container for property names or smth
            if(section < DefaultColumnsCount)
            {
                switch (section) {
                case IdColumn:
                    headerName = tr("Id");
                    break;
                default:
                    break;
                }
            }
            else
            {
                const std::string property = mPropertyNames.at(section-DefaultColumnsCount);
                QString headerStr = QString::fromStdString(property).toLower();
                headerStr[0] = headerStr[0].toUpper();
                headerName.setValue(headerStr);
            }
        }
        else
        {
            headerName = QString::number(section);
        }
    }
    return headerName;
}

/*!
 * \brief RevisionModel::graph Returns graph that holds data about revisions.
 * \return Boost graph.
 */
revision_graph RevisionModel::graph() const
{
    return mGraph;
}

