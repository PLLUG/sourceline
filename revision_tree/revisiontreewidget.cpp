#include "revisiontreewidget.h"
#include <iostream>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/property_maps/container_property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <QPainter>
#include <QPaintEvent>

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QOpenGLWidget{parent},
    mVertexBuffer{QOpenGLBuffer::VertexBuffer}
{
}

RevisionTreeWidget::~RevisionTreeWidget()
{
    mVertexBuffer.destroy();
}

void RevisionTreeWidget::setGraph(const revision_graph &pGraph)
{
    mGraph = pGraph;
    boost::vertices(mGraph);
    boost::associative_property_map<IndexMap> colIndex(mColumnMap);
    boost::associative_property_map<IndexMap> rowIndex(mRowMap);
    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
       put(colIndex, v, -1);
    }

    //perform topological sort
    std::vector< vertex > c;
    topological_sort(mGraph, std::back_inserter(c));
    int row = boost::num_vertices(mGraph);
    for ( std::vector< vertex >::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
    {
        put(rowIndex, *ii, --row);
        put(colIndex, *ii, row);
    }
}

void RevisionTreeWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();

//    if(!mVertexBuffer.isCreated())
//    {
//        mVertexBuffer.create();
//        mVertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
//        mVertexBuffer.bind();
//    }
}

void RevisionTreeWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w,h);
}

void RevisionTreeWidget::paintGL()
{
    QOpenGLWidget::paintGL();
    glClearColor(1,1,1,1);
}

void RevisionTreeWidget::paintEvent(QPaintEvent *e)
{
    QOpenGLWidget::paintEvent(e);

    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);

    const float width = 10;
    const float radius = 2;

    boost::associative_property_map<IndexMap> colIndex(mColumnMap);
    boost::associative_property_map<IndexMap> rowIndex(mRowMap);

    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
       int row = get(rowIndex, v);
       int col = get(colIndex, v);
       painter.drawEllipse(QPoint(width*col, width*row), radius, radius);
    }

    BGL_FORALL_EDGES(e, mGraph, revision_graph)
    {
        int sourceRow = get(rowIndex, boost::source(e, mGraph));
        int sourceCol = get(colIndex, boost::source(e, mGraph));
        int targetRow = get(rowIndex, boost::target(e, mGraph));
        int targetCol = get(colIndex, boost::target(e, mGraph));
        painter.drawLine(QPoint(width*sourceCol, width*sourceRow), QPoint(width*targetCol, width*targetRow));
    }
}

void RevisionTreeWidget::resizeEvent(QResizeEvent *e)
{
    QOpenGLWidget::resizeEvent(e);
}

bool RevisionTreeWidget::event(QEvent *e)
{
    QOpenGLWidget::event(e);
}

