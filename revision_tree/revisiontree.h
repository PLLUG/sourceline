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

    void setModel(RevisionModel *model);

    int rowHeight() const;
    void setRowHeight(int rowHeight);

private slots:
    void slotTableScrollChanged(int value);
    void slotGraphScrollChanged(int value);

private:
    void clearGraph();
    void read();

private:
    Ui::RevisionTree *ui;

    revision_graph mGraph;
    int mRowHeight;

};

#endif // REVISIONTREE_H
