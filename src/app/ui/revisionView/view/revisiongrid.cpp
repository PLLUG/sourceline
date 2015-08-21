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

#include "revisiongrid.h"
#include "../revisionnode.h"
#include "revisionnodeitem.h"

#include <QPainter>
#include <QDebug>
#include <QWheelEvent>

RevisionGrid::RevisionGrid()
{
    mSize = QSizeF(250, 250);
//    setFlag(ItemIsMovable);
    mRoot = new RevisionNode();
}

void RevisionGrid::setBoundingRect(const QSizeF pSize)
{
    prepareGeometryChange();
    mSize = pSize;
}

void RevisionGrid::setBoundingRect(qreal pWidth, qreal pHeight)
{
    setBoundingRect(QSizeF(pWidth, pHeight));
}

void RevisionGrid::view(RevisionNode *pRoot)
{
    mRoot = pRoot;
    drawNode(mRoot, gridStep());
    drawLines(pRoot);
}

QRectF RevisionGrid::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

QPoint RevisionGrid::startPoint() const
{
    return boundingRect().bottomLeft().toPoint();
}

int RevisionGrid::gridStep() const
{
    return 20;
}

void RevisionGrid::drawText(const QString &pText, RevisionNodeItem *pItem)
{
    mText = pText;
    mTextPos = pItem->pos() + pItem->boundingRect().topRight();
    update();
}

void RevisionGrid::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    Q_UNUSED(pOption)
    Q_UNUSED(pWidget)
    pPainter->setRenderHint(QPainter::Antialiasing);
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(QBrush(QColor(100, 100, 100)));
    pPainter->drawRoundedRect(boundingRect(), 5, 5);

    if (!mText.isEmpty())
    {
        QFontMetricsF lFontMetrics(pPainter->font());
        QRectF lRect (mTextPos + QPointF(10, 0), QSizeF(lFontMetrics.width(mText) + 5, lFontMetrics.height() + 5));
        pPainter->setBrush(QColor(150, 150, 150));
        pPainter->drawRoundedRect(lRect, 3, 3);
        pPainter->setPen(Qt::white);
        pPainter->drawText(lRect, mText, QTextOption(Qt::AlignCenter));
    }
}

bool RevisionGrid::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *e = dynamic_cast<QWheelEvent *>(event);
        static qreal sc = 1.0;
        if (e->modifiers() & Qt::ControlModifier)
        {
            if (e->delta() > 0)
            {
                sc += 0.1;
            }
            else
            {
                sc -= 0.1;
            }
            setScale(sc);
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void RevisionGrid::drawNode(RevisionNode *pItem, int pCurrentCol)
{
    static int lCurrentRow = gridStep();
    int lCurrentColumn = pCurrentCol;
    RevisionNode *lNode = pItem;
    while (lNode != 0)
    {
        RevisionNodeItem *lItem = new RevisionNodeItem(lNode, this);
        lNode->mGraphicsItem = lItem;
        lItem->setPos(startPoint() + QPoint(lCurrentColumn, -lCurrentRow));
        lCurrentRow += gridStep();
        if (!lNode->mBranches.isEmpty())
        {
            for (int i = 0; i < lNode->mBranches.size(); ++i)
            {
                RevisionNodeItem *lIt = new RevisionNodeItem(lNode->mBranches.at(i), this);
                lNode->mBranches.at(i)->mGraphicsItem = lIt;
                lIt->setPos(startPoint() + QPoint(lCurrentColumn + gridStep() * (i+1), -lCurrentRow));
                lCurrentRow += gridStep();
            }
            for (int i = 0; i < lNode->mBranches.size(); ++i)
            {
                if (lNode->mBranches.at(i)->mChild)
                {
                    drawNode(lNode->mBranches.at(i)->mChild, pCurrentCol + gridStep() * (i + 1));
                }
            }
        }
        lNode = lNode->mChild;
    }
}

void RevisionGrid::drawLines(RevisionNode *pRoot)
{
    RevisionNode *lNext = pRoot;
    while (lNext)
    {
        if (lNext->mMergeTo)
        {
            drawBezier(lNext->mGraphicsItem, lNext->mMergeTo->mGraphicsItem);
        }
        if (lNext->mChild)
        {
            drawLine(lNext->mGraphicsItem, lNext->mChild->mGraphicsItem);
            if (!lNext->mBranches.isEmpty())
            {
                for (int i = 0; i < lNext->mBranches.size(); ++i)
                {
                    drawBezier(lNext->mGraphicsItem, lNext->mBranches.at(i)->mGraphicsItem);
                    drawLines(lNext->mBranches.at(i));
                }
            }
            lNext = lNext->mChild;
        }
        else
        {
            if (!lNext->mBranches.isEmpty())
            {
                for (int i = 0; i < lNext->mBranches.size(); ++i)
                {
                    drawBezier(lNext->mGraphicsItem, lNext->mBranches.at(i)->mGraphicsItem);
                    drawLines(lNext->mBranches.at(i));
                }
            }
            break;
        }
    }
}

void RevisionGrid::drawBezier(RevisionNodeItem *pFrom, RevisionNodeItem *pTo)
{
    QGraphicsPathItem *lItem = new QGraphicsPathItem(this);
    QPainterPath lPath;
    QRectF lRect(pFrom->pos() + pFrom->boundingRect().center(), pTo->pos() + pTo->boundingRect().center());
    lPath.moveTo(lRect.topLeft());
    QPointF lPoint1 = QPointF(lRect.bottomLeft().x(), lRect.bottomLeft().y() - lRect.height() - gridStep() * 0.7);
    QPointF lPoint2 = lRect.topRight();
    lPath.cubicTo(lPoint1, lPoint2, lRect.bottomRight());
    lItem->setPen(QPen(Qt::red));
    lItem->setPath(lPath);

//    QGraphicsLineItem *line = new QGraphicsLineItem(this);
//    line->setLine(QLineF(c1, c2));
}

void RevisionGrid::drawLine(RevisionNodeItem *pFrom, RevisionNodeItem *pTo)
{
    QGraphicsLineItem *lLine = new QGraphicsLineItem(this);
    lLine->setPen(QPen(Qt::red));
    lLine->setLine(QLineF(pFrom->pos() + pFrom->boundingRect().center(), pTo->pos() + pTo->boundingRect().center()));
}
