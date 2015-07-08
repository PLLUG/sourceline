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

#include "revisionview.h"
#include "ui_revisionview.h"

#include "revisionView/view/abstractgraphicsview.h"

#include <QResizeEvent>
#include <QDebug>

RevisionView::RevisionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RevisionView),
    mView(0)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene;
    ui->graphicsView->setScene(mScene);

    mView = new AbstractGraphicsView;
    mModel = new RevisionTableModel;
    mView->setModel(mModel);
    mScene->addItem(mView);

    connect(mView, SIGNAL(updateUI()), this, SLOT(updateUI()));
}

RevisionView::~RevisionView()
{
    delete ui;
}

RevisionTableModel *RevisionView::model() const
{
    return mModel;
}

void RevisionView::resizeEvent(QResizeEvent *event)
{
    updateUI();
    QWidget::resizeEvent(event);
}

void RevisionView::updateUI()
{
    QRect rect = ui->graphicsView->rect();
    if ( rect.height() > mView->rect().height() )
    {
        mView->setSize(QSizeF(rect.width() - 2, rect.height() - 2));
        mScene->setSceneRect(mView->boundingRect());
    }
    else
    {
        mView->setSize(QSizeF(rect.width() - 20, mView->boundingRect().height()));
        mScene->setSceneRect(mView->rect());
    }
}
