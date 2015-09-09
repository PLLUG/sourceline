#ifndef REVISIONTREE_H
#define REVISIONTREE_H
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
#include <QWidget>
#include "revisionmodel.h"
#include <vector>

namespace Ui {
class RevisionTree;
}
/*!
 * \brief The RevisionTree class Draws 'revision tree' (graph).
 */
class RevisionTree : public QWidget
{
    Q_OBJECT

public:
    explicit RevisionTree(QWidget *parent = 0);
    ~RevisionTree();

    void read();

    int rowHeight() const;
    void setRowHeight(int rowHeight);

    void addNode(const std::string &pParentID, const RevisionNode &pNodeInfo);
    void putProperty(const std::string &pRecepientId, const std::string &property, const QVariant &value);

private slots:
    void slotTableScrollChanged(int pValue);
    void slotGraphScrollChanged(int pValue);

private:
    void clearGraph();

private:
    Ui::RevisionTree *ui;

    int mRowHeight;
    RevisionModel *mModel;
};

#endif // REVISIONTREE_H
