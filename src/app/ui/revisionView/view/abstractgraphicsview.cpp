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


#include "abstractgraphicsview.h"
#include "abstractrevisiondelegate.h"
#include "../parameters.h"
#include "../revisionitem.h"
#include "../revisiontablemodel.h"
#include "../creator.h"

#include <QPainter>
#include <QAbstractItemModel>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

AbstractGraphicsView::AbstractGraphicsView()
{
    mSize = QSizeF(150, 150);
    setFlag(ItemClipsChildrenToShape);
    mModel = nullptr;
}

AbstractGraphicsView::~AbstractGraphicsView()
{
    delete mModel;
}

QRectF AbstractGraphicsView::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

QRectF AbstractGraphicsView::rect() const
{
    return childrenBoundingRect();
}

void AbstractGraphicsView::setSize(qreal pWidth, qreal pHeight)
{
    setSize(QSizeF(pWidth, pHeight));
}

void AbstractGraphicsView::setSize(const QSizeF &pSize)
{
    prepareGeometryChange();
    mSize = pSize;
    updateGeometry();
}

void AbstractGraphicsView::setItemDelegate(AbstractRevisionDelegate *pItem)
{
    Q_UNUSED(pItem)
    //
}

void AbstractGraphicsView::setModel(QAbstractItemModel *pModel)
{
    mModel = pModel;
    connect(mModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slotModelChanged()));
    updateModelData();
    updateGeometry();
}

void AbstractGraphicsView::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    Q_UNUSED(pOption)
    Q_UNUSED(pWidget)
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(Parameters::ViewBackground());
    pPainter->drawRect(boundingRect());
}

void AbstractGraphicsView::updateModelData()
{
    if (mModel)
    {
        while (mItems.size() != mModel->rowCount())
        {
            if (mItems.size() > mModel->rowCount())
            {
                AbstractRevisionDelegate *lTempDelegate = mItems.last();
                mItems.removeLast();
                delete lTempDelegate;
            }
            else
            {
                mItems.append(new AbstractRevisionDelegate(this));
                connect(mItems.last(), SIGNAL(needRequestFromView(AbstractRevisionDelegate*)),
                        this, SLOT(slotRequestForItem(AbstractRevisionDelegate *)));
                connect(mItems.last(), SIGNAL(commit(AbstractRevisionDelegate*)), this, SLOT(commitClicked(AbstractRevisionDelegate*)));
                connect(mItems.last(), SIGNAL(branch(AbstractRevisionDelegate*)), this, SLOT(branchClicked(AbstractRevisionDelegate*)));
            }
        }

        for (int i = 0; i < mItems.size(); ++i)
        {
            AbstractRevisionDelegate *lTempDelegate = mItems.at(i);
            lTempDelegate->setData(AbstractRevisionDelegate::DR_Drawing, mModel->data(mModel->index(i, 0), Qt::DisplayRole));
            lTempDelegate->setData(AbstractRevisionDelegate::DR_Text, mModel->data(mModel->index(i, 2), Qt::DisplayRole));
            lTempDelegate->setData(AbstractRevisionDelegate::DR_Id, mModel->data(mModel->index(i, 1), Qt::DisplayRole));
        }
    }
}

QRectF AbstractGraphicsView::resizeRect() const
{
    return QRectF (boundingRect().bottomRight() + QPointF(-20, -20), boundingRect().bottomRight());
}

void AbstractGraphicsView::slotRequestForItem(AbstractRevisionDelegate *pItem)
{
    for (int i = 1; i < mItems.size(); ++i)
    {
        if (mItems.at(i) == pItem)
        {
            pItem->setPreviousState(QPointF(0, i * mItems.at(i - 1)->boundingRect().height()) + QPointF(0, 2 * i));
            break;
        }
    }
}

void AbstractGraphicsView::slotModelChanged()
{
    updateModelData();
    updateGeometry();
}

void AbstractGraphicsView::branchClicked(AbstractRevisionDelegate* pDelegate)
{
    QMap<QString, QVariant> lData = pDelegate->data(Qt::DisplayRole).toMap();
    QPair<int, int> lPos = qMakePair(lData.value("x").toInt(), lData.value("y").toInt());
    Creator *lCreator = dynamic_cast<RevisionTableModel*>(mModel)->graph();
    RevisionItem *lItem = lCreator->item(lPos.second);
    lCreator->switchTo(lItem->parentBranch());
    lCreator->addBranch(new RevisionItem(tr("hello")), tr("new branch"));
    updateModelData();
    updateGeometry();
    emit updateUI();
}

void AbstractGraphicsView::commitClicked(AbstractRevisionDelegate* pDelegate)
{
    QMap<QString, QVariant> lData = pDelegate->data(Qt::DisplayRole).toMap();
    QPair<int, int> lPos = qMakePair(lData.value("x").toInt(), lData.value("y").toInt());
    Creator *lCreator = dynamic_cast<RevisionTableModel*>(mModel)->graph();
    RevisionItem *lItem = lCreator->item(lPos.second);
    lCreator->switchTo(lItem->parentBranch());
    lCreator->addCommit(new RevisionItem(tr("test")));
    updateModelData();
    updateGeometry();
    emit updateUI();
}

ModelIndex AbstractGraphicsView::createIndex(int pRow, int pColumn)
{
    return ModelIndex(pRow, pColumn);
}

void AbstractGraphicsView::updateGeometry()
{
    if (!mItems.isEmpty())
    {
        mItems.first()->setSize(mSize.width(), 21);
        mItems.first()->setPos(0, 0);
        for (int i = 1; i < mItems.size(); ++i)
        {
            mItems[i]->setSize(mSize.width(), 21);
            mItems[i]->setPos(mItems[i - 1]->pos() + mItems[i-1]->boundingRect().bottomLeft() + QPointF(0, 1));
        }
    }
}
