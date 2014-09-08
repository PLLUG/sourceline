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

#ifndef REVISIONWIDGET_H
#define REVISIONWIDGET_H

#include <QWidget>
#include "revisionView/revisiontablemodel.h"

QT_FORWARD_DECLARE_CLASS(AbstractGraphicsView)
QT_FORWARD_DECLARE_CLASS(QGraphicsScene)

namespace Ui {
class RevisionView;
}

class RevisionView : public QWidget
{
    Q_OBJECT

public:
    explicit RevisionView(QWidget *parent = 0);
    ~RevisionView();

    RevisionTableModel *data() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::RevisionView *ui;

    AbstractGraphicsView *mView;
    QGraphicsScene *mScene;
    RevisionTableModel *mModel;

private slots:
    void updateUI();
};

#endif // REVISIONWIDGET_H
