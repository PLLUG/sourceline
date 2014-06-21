#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // GRAPHICSVIEW_H
