#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
#include <QOpenGLWidget>
#include "revisionmodel.h"

#include <boost/graph/topology.hpp>

using IndexMap = std::map<vertex, int>;

using Point = boost::rectangle_topology<>::point_type;

/*!
 * \brief The RevisionTreeWidget class Paints revision graph
 */
class RevisionTreeWidget : public QOpenGLWidget
{
public:
    RevisionTreeWidget(QWidget* parent = nullptr);
    ~RevisionTreeWidget();

    void setGraph(const revision_graph &pGraph);

    static vertex findRoot(const revision_graph &pGraph);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    bool event(QEvent *e) override;

private:
    revision_graph mGraph;

    IndexMap mColumnMap;
    IndexMap mRowMap;

    std::map<vertex, Point>mPositionMap;

};

#endif // REVISIONTREEWIDGET_H
