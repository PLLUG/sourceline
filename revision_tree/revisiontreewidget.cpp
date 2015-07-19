#include "revisiontreewidget.h"
#include <iostream>
#include <boost/graph/topological_sort.hpp>

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QOpenGLWidget{parent}
{

}

void RevisionTreeWidget::setGraph(const revision_graph &pGraph)
{
    mGraph = pGraph;

    //perform topological sort
    std::vector< vertex > c;
    topological_sort(mGraph, std::back_inserter(c));
    std::cout << "A topological ordering: ";
    for ( std::vector< vertex >::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
    {
        std::cout << *ii << " ";
    }
    std::cout << std::endl;
}

void RevisionTreeWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();
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
}

void RevisionTreeWidget::resizeEvent(QResizeEvent *e)
{
    QOpenGLWidget::resizeEvent(e);
}

bool RevisionTreeWidget::event(QEvent *e)
{
    QOpenGLWidget::event(e);
}

