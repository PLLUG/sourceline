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
#include "revisiontablemodel.h"

QT_FORWARD_DECLARE_CLASS(AbstractGraphicsView)
QT_FORWARD_DECLARE_CLASS(QGraphicsScene)

namespace Ui {
class RevisionWidget;
}

class RevisionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RevisionWidget(QWidget *parent = 0);
    ~RevisionWidget();

    RevisionTableModel *data() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::RevisionWidget *ui;

    AbstractGraphicsView *mView;
    QGraphicsScene *mScene;
    RevisionTableModel *mModel;
};

#endif // REVISIONWIDGET_H
