#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
#include "revisionmodel.h"
#include "revisionvertex.h"
#include <QWidget>

#include <boost/graph/topology.hpp>

using VertexIntMap = std::map<vertex, int>;
using Point = boost::rectangle_topology<>::point_type;

/*!
 * \brief The RevisionTreeWidget class Paints revision graph
 */
class RevisionTreeWidget : public QWidget
{
public:
    RevisionTreeWidget(QWidget* parent = nullptr);
    ~RevisionTreeWidget();

    void setGraph(const revision_graph &pGraph);

    float offset() const;
    void setOffset(float offset);

    int radius() const;
    void setRadius(int radius);

    float width() const;
    void setWidth(float width);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;

private:
    std::vector<vertex> getSortedGraphByTime(const revision_graph &graph);
    static vertex findRoot(const revision_graph &pGraph);


    std::vector<RevisionVertex> revisionVertexVector(const revision_graph &pGraph);

private:

    revision_graph mGraph;
    float mOffset;
    int mRadius;
    float mWidth;

    VertexIntMap mColumnMap;
    VertexIntMap mRowMap;

    std::map<vertex, Point>mPositionMap;

    VertexIntMap mTestBFSOrderMap;
};

#endif // REVISIONTREEWIDGET_H
