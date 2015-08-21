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
    {
        return mGraph->field()->height();
    }
    return 0;
}

int RevisionTableModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant RevisionTableModel::data(const QModelIndex &pIndex, int pRole) const
{
    if (!mGraph)
    {
        return QVariant();
    }
    if (pRole == Qt::DisplayRole)
    {
        if (pIndex.column() == 2)
        {
            if (mGraph->item(pIndex.row()))
            {
                return mGraph->item(pIndex.row())->message();
            }
        }
        else
        {
            if (pIndex.column() == 1)
            {
            }
            else
            {
                if (pIndex.column() == 0)
                {
                    if (mGraph->item(pIndex.row()))
                    {
                        QMap<QString, QVariant> rMap;
                        RevisionItem *lItem = mGraph->item(pIndex.row());
                        Branch *lBranch = lItem->parentBranch();
                        if (lBranch)
                        {
                            rMap.insert(tr("pos"), lItem->x());
                            rMap.insert(tr("head"), bool(lBranch->head() == lItem));
                            rMap.insert(tr("branches"), mGraph->brPos(lItem));
                            rMap.insert(tr("x"), lItem->x());
                            rMap.insert(tr("y"), lItem->y());
                            rMap.insert(tr("branchesBefore"), mGraph->branchesBefore(lItem));
                            rMap.insert(tr("branchesAfter"), mGraph->branchesAfter(lItem));
                            return rMap;
                        }
                    }
                }
            }
        }
    }
    if (pRole == Qt::TextAlignmentRole)
    {
        if (pIndex.column() == 1)
        {
            return Qt::AlignCenter;
        }
    }
    return QVariant();
}

QVariant RevisionTableModel::headerData(int pSection, Qt::Orientation pOrientation, int pRole) const
{
    if (pRole == Qt::DisplayRole && pOrientation == Qt::Horizontal)
    {
        if (pSection == 0)
        {
            return tr("Graph");
        }
        if (pSection == 1)
        {
            return tr("rev.");
        }
        if (pSection == 2)
        {
            return tr("Message");
        }
    }
    return QVariant();
}

void RevisionTableModel::dataChange()
{
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

Creator *RevisionTableModel::graph() const
{
    return mGraph;
}
