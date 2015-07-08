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

void AbstractRevisionDelegate::setSize(qreal width, qreal height)
{
    prepareGeometryChange();
    mSize.setHeight(height);
    mSize.setWidth(width);

    updateBubblePosition();
}

void AbstractRevisionDelegate::setPreviousState(const QPointF &pos)
{
    mPreviousState = pos;
}

void AbstractRevisionDelegate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Parameters::ItemBoudingRectPen());
    painter->drawRoundedRect(boundingRect(), 4, 4);

    QColor c;
    if ( option->state &QStyle::State_Selected )
    {
        c = Parameters::ItemSelectedColor();
    }
    else
    {
        c = Parameters::ItemBackground();
    }
    painter->fillRect(option->rect, c);
    QMap<QString, QVariant> drawingData = data(DR_Drawing).toMap();
    if ( drawingData.contains("pos") )
    {
        painter->setPen(Parameters::LinesColor());
        int pos = drawingData.value("pos").toInt() + 1;
        mBubblePos = pos;

        if ( drawingData.contains("branches") )
        {
            QList<QVariant> br = drawingData.value("branches").toList();
            int linePos;
            for (int i = 0; i < br.size() ; ++i)
            {
                linePos = br.at(i).toInt();
                QPainterPath path;
                path.moveTo(qreal((pos) * mGridStep), qreal(option->rect.center().y()));
                QRectF r(qreal((pos) * mGridStep), qreal(option->rect.center().y()),
                         qreal( (linePos - pos + 1) * mGridStep), qreal(option->rect.height() / 2));
                QPointF c1 = QPointF(r.x(), r.center().y());//r.bottomLeft();
                QPointF c2 = QPointF(r.right(), r.center().y());//r.topRight() + QPointF(0, 2);
                path.cubicTo(c1, c2, r.bottomRight());
                painter->drawPath(path);
            }
        }
        if (drawingData.contains("branchesBefore"))
        {
            QList<QVariant> d = drawingData.value("branchesBefore").toList();
            if (!d.isEmpty())
            {
                for (int i = 0; i < d.size(); ++i)
                    painter->drawLine(QPoint((d.at(i).toInt() + 1) * mGridStep, option->rect.y()),
                                      QPoint((d.at(i).toInt() + 1) * mGridStep, option->rect.bottom()));
            }
        }
        if ( drawingData.contains("head") )
        {
            bool isHead = drawingData.value("head").toBool();
            if ( isHead )
                painter->drawLine(QPoint(pos * mGridStep, option->rect.y()), QPoint(pos * mGridStep, option->rect.center().y()));
            else
                painter->drawLine(QPoint(pos * mGridStep, option->rect.y()), QPoint(pos * mGridStep, option->rect.bottom()));
        }
        if ( drawingData.contains("branchesAfter") )
        {
            QList<QVariant> after = drawingData.value("branchesAfter").toList();
            int value;
            for (int i = 0; i < after.size(); ++i)
            {
                value = after.at(i).toInt();
                painter->drawLine(QPoint((value + 1) * mGridStep, option->rect.y()),
                                  QPoint((value + 1)* mGridStep, option->rect.bottom()));
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
    QMenu menu;
    QMap<QString, QVariant>d = data(DR_Drawing).toMap();
    if (d.contains("head"))
        if (d.value("head").toBool()) {
            QAction *commit = menu.addAction("Commit");
            connect(commit, SIGNAL(triggered()), this, SLOT(commitActionTriggered()));
        }
    QAction *branch = menu.addAction("Branch");
    connect(branch, SIGNAL(triggered()), this, SLOT(branchActionTriggered()));
    menu.exec(event->screenPos());
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
