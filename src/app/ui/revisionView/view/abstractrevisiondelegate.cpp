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

#include "abstractrevisiondelegate.h"
#include "bubble.h"
#include "../parameters.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QMenu>
#include <QDebug>
#include <QPropertyAnimation>

AbstractRevisionDelegate::AbstractRevisionDelegate(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
//    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    mAnim = new QPropertyAnimation(this, "Pos");
    mAnim->setDuration(800);
    mAnim->setPropertyName("Pos");

    mBubble = new Bubble;
    mBubble->setParentItem(this);
    connect(mBubble, SIGNAL(updateBubble()), this, SLOT(updateBubblePosition()));
    mBubble->setPen(QPen(Qt::darkCyan));
    mGridStep = Parameters::GridStep;

    updateBubblePosition();
}

QRectF AbstractRevisionDelegate::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void AbstractRevisionDelegate::setSize(qreal pWidth, qreal pHeight)
{
    prepareGeometryChange();
    mSize.setHeight(pHeight);
    mSize.setWidth(pWidth);

    updateBubblePosition();
}

void AbstractRevisionDelegate::setPreviousState(const QPointF &pPos)
{
    mPreviousState = pPos;
}

void AbstractRevisionDelegate::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    pPainter->setRenderHint(QPainter::Antialiasing);
    pPainter->setPen(Parameters::ItemBoudingRectPen());
    pPainter->drawRoundedRect(boundingRect(), 4, 4);

    QColor lColor;
    if (pOption->state &QStyle::State_Selected)
    {
        lColor = Parameters::ItemSelectedColor();
    }
    else
    {
        lColor = Parameters::ItemBackground();
    }

    pPainter->fillRect(pOption->rect, lColor);
    QMap<QString, QVariant> lDrawingData = data(DR_Drawing).toMap();
    if (lDrawingData.contains(tr("pos")))
    {
        pPainter->setPen(Parameters::LinesColor());
        int lPos = lDrawingData.value(tr("pos")).toInt() + 1;
        mBubblePos = lPos;

        if (lDrawingData.contains(tr("branches")))
        {
            QList<QVariant> lBranches = lDrawingData.value(tr("branches")).toList();
            for (int i = 0; i < lBranches.size() ; ++i)
            {
                int lLinePos = lBranches.at(i).toInt();
                QPainterPath lPath;
                lPath.moveTo(qreal((lPos) * mGridStep), qreal(pOption->rect.center().y()));
                QRectF lRect(qreal((lPos) * mGridStep), qreal(pOption->rect.center().y()),
                         qreal( (lLinePos - lPos + 1) * mGridStep), qreal(pOption->rect.height() / 2));
                QPointF lPoint1 = QPointF(lRect.x(), lRect.center().y());//r.bottomLeft();
                QPointF lPoint2 = QPointF(lRect.right(), lRect.center().y());//r.topRight() + QPointF(0, 2);
                lPath.cubicTo(lPoint1, lPoint2, lRect.bottomRight());
                pPainter->drawPath(lPath);
            }
        }
        if (lDrawingData.contains(tr("branchesBefore")))
        {
            QList<QVariant> lBranches = lDrawingData.value(tr("branchesBefore")).toList();
            if (!lBranches.isEmpty())
            {
                for (int i = 0; i < lBranches.size(); ++i)
                    pPainter->drawLine(QPoint((lBranches.at(i).toInt() + 1) * mGridStep, pOption->rect.y()),
                                      QPoint((lBranches.at(i).toInt() + 1) * mGridStep, pOption->rect.bottom()));
            }
        }
        if (lDrawingData.contains(tr("head")))
        {
            bool lIsHead = lDrawingData.value(tr("head")).toBool();
            if (lIsHead)
            {
                pPainter->drawLine(QPoint(lPos * mGridStep, pOption->rect.y()), QPoint(lPos * mGridStep, pOption->rect.center().y()));
            }
            else
            {
                pPainter->drawLine(QPoint(lPos * mGridStep, pOption->rect.y()), QPoint(lPos * mGridStep, pOption->rect.bottom()));
            }
        }

        if (lDrawingData.contains(tr("branchesAfter")))
        {
            QList<QVariant> after = lDrawingData.value(tr("branchesAfter")).toList();
            for (int i = 0; i < after.size(); ++i)
            {
                int lValue = after.at(i).toInt();
                pPainter->drawLine(QPoint((lValue + 1) * mGridStep, pOption->rect.y()),
                                  QPoint((lValue + 1)* mGridStep, pOption->rect.bottom()));
            }
        }
    }

//    QString text = data(DR_Text).toString();

//    QRectF rect = boundingRect();
//    rect.setX(rect.x() + 80);
//    rect.setWidth(rect.width() - 80);
//    painter->setPen(Qt::white);
//    painter->drawText(rect, text + QString(" - %1").arg(data(DR_Id).toString()), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
}

void AbstractRevisionDelegate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit needRequestFromView(this);
//    mAnim->setStartValue(mapToParent(event->pos()) - event->pos());
//    mAnim->setEndValue(mPreviousState);
//    mAnim->start();
    QGraphicsItem::mouseReleaseEvent(event);
}

void AbstractRevisionDelegate::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu lMenu;
    QMap<QString, QVariant> lMapD = data(DR_Drawing).toMap();
    if (lMapD.contains(tr("head")))
    {
        if (lMapD.value(tr("head")).toBool())
        {
            QAction *lCommit = lMenu.addAction(tr("Commit"));
            connect(lCommit, SIGNAL(triggered()), this, SLOT(commitActionTriggered()));
        }
    }
    QAction *lBranch = lMenu.addAction(tr("Branch"));
    connect(lBranch, SIGNAL(triggered()), this, SLOT(branchActionTriggered()));
    lMenu.exec(event->screenPos());
}

void AbstractRevisionDelegate::updateBubblePosition()
{
    if (mBubble)
    {
        mBubble->setPos( QPointF( mGridStep * (data(DR_Drawing).toMap().value("pos").toInt() + 1), boundingRect().center().y() ) - mBubble->boundingRect().center() );
    }
}

void AbstractRevisionDelegate::commitActionTriggered()
{
    emit commit(this);
}

void AbstractRevisionDelegate::branchActionTriggered()
{
    emit branch(this);
}
