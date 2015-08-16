#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
#include "revisionmodel.h"
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

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;

private:
    std::vector<vertex> getSortedGraphByTime(const revision_graph &graph);
    static vertex findRoot(const revision_graph &pGraph);

private:
    /*!
     * \brief The VertexType enum repressents types of vertex.
     *
     * Vertex type is defined according to how many edges enter in vertex and
     * how many exit from.
     */
    enum VertexType
    {
        /// Number of input edges = 0
        vtNoIn,
        /// Number of output edges = 0
        vtNoOut,
        /// Number of input edges = 1, Number of output edges = 1
        vtOneInOneOut,
        /// Number of input edges > 1, Number of output edges > 1
        vtManyInManyOut,
        /// Number of input edges = 1, Number of output edges > 1
        vtOneInManyOut,
        /// Number of input edges > 1, Number of output edges = 1
        vtManyInOneOut
    };

    revision_graph mGraph;

    VertexIntMap mColumnMap;
    VertexIntMap mRowMap;

    std::map<vertex, Point>mPositionMap;
};

#endif // REVISIONTREEWIDGET_H
