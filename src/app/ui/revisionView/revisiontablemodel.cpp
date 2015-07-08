/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Volodymyr Kochyn  (vovakochyn@gmail.com)                      ***
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

#include "revisiontablemodel.h"
#include "createtree.h"
#include "creator.h"
#include "revisionnode.h"
#include "revisionitem.h"
#include "branch.h"

#include <QDebug>

RevisionTableModel::RevisionTableModel()
{
    CreateTree ct;
    mRoot = ct.create();

    mGraph = new Creator;
}

int RevisionTableModel::rowCount(const QModelIndex &) const
{
    if (mGraph)
        return mGraph->field()->height();
    return 0;
}

int RevisionTableModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant RevisionTableModel::data(const QModelIndex &index, int role) const
{
    if (!mGraph)
        return QVariant();
    if ( role == Qt::DisplayRole )
    {
        if ( index.column() == 2 )
        {
            if (mGraph->item(index.row()))
                return mGraph->item(index.row())->message();
        }
        else if ( index.column() == 1 )
        {
        }
        else if ( index.column() == 0 )
        {
            if (mGraph->item(index.row()))
            {
                QMap<QString, QVariant> map;
                RevisionItem *item = mGraph->item(index.row());
                Branch *branch = item->parentBranch();
                if (branch)
                {
                    map.insert("pos", item->x());
                    map.insert("head", bool(branch->head() == item));
                    map.insert("branches", mGraph->brPos(item));
                    map.insert("x", item->x());
                    map.insert("y", item->y());
                    map.insert("branchesBefore", mGraph->branchesBefore(item));
                    map.insert("branchesAfter", mGraph->branchesAfter(item));
                    return map;
                }
            }
        }
    }
    if ( role == Qt::TextAlignmentRole )
    {
        if ( index.column() == 1 )
            return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant RevisionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if ( section == 0 )
            return "Graph";
        if ( section == 1 )
            return "rev.";
        if ( section == 2 )
            return "Message";
    }
    return QVariant();
}

void RevisionTableModel::dataChange()
{
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

Creator *RevisionTableModel::graph() const { return mGraph; }
