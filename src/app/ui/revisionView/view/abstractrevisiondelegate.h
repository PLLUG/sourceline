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

#ifndef ABSTRACTREVISIONDELEGATE_H
#define ABSTRACTREVISIONDELEGATE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPropertyAnimation>


QT_FORWARD_DECLARE_CLASS(QPropertyAnimation)
QT_FORWARD_DECLARE_CLASS(Bubble)

class AbstractRevisionDelegate : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF Pos READ pos WRITE setPos)
    friend class Bubble;
public:
    enum DataRole { DR_Drawing, DR_Text, DR_Id };
    explicit AbstractRevisionDelegate(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void setSize(qreal pWidth, qreal pHeight);

    void setPreviousState(const QPointF &pPos);

signals:
    void needRequestFromView(AbstractRevisionDelegate *pItem);

    void commit(AbstractRevisionDelegate*);
    void branch(AbstractRevisionDelegate*);

protected:
    void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget = 0);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

private:
    QSizeF mSize;
    QPointF mPreviousState;
    QPropertyAnimation *mAnim;
    Bubble *mBubble;
    int mGridStep;
    QMap<QString, QVariant> mData;
    int mBubblePos;

private slots:
    void updateBubblePosition();
    void commitActionTriggered();
    void branchActionTriggered();
};

#endif // ABSTRACTREVISIONDELEGATE_H
