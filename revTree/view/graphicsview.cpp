#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    if ( scene() )
        scene()->setSceneRect(rect());
}
