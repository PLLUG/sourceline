#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
#include "revisionmodel.h"
#include "revisionvertex.h"
#include <QWidget>

using VertexIntMap = std::map<vertex, int>;

/*!
 * \brief The RevisionTreeWidget class Paints revision graph.
 */
class RevisionTreeWidget : public QWidget
{
public:
    RevisionTreeWidget(QWidget* parent = nullptr);
    ~RevisionTreeWidget();

    void setGraph(const revision_graph &pGraph);

    int radius() const;
    void setRadius(int radius);

    float rowHeight() const;
    void setRowHeight(float width);

    float getLeftOffset() const;
    void setLeftOffset(float leftOffset);

    float getTopOffset() const;
    void setTopOffset(float topOffset);

    float getBottomOffset() const;
    void setBottomOffset(float bottomOffset);

    int getStep() const;
    void setStep(int step);

    int getEdgeOffset() const;
    void setEdgeOffset(int edgeOffset);

    static int maxColumnFromColumnMap(const VertexIntMap &pColumnMap);

    float columnWidth() const;
    void setColumnWidth(float width);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    std::vector<vertex> getSortedGraphByTime(const revision_graph &graph);
    static vertex findRoot(const revision_graph &pGraph);
    std::vector<RevisionVertex> revisionVertexVector(const revision_graph &pGraph);

private:
    revision_graph mGraph;
    float mLeftOffset;
    float mTopOffset;
    float mBottomOffset;
    // Radius of vertex
    int mRadius;
    // Radius of round of edges
    int mStep;
    // Offset from center of vertex to edges, that are branches or merges
    int mEdgeOffset;
    float mRowHeight;
    float mColumnWidth;

    VertexIntMap mColumnMap;
    VertexIntMap mRowMap;

    std::vector<RevisionVertex> mRevisionVertexes;
    VertexIntMap mTestOrderMap;
};

#endif // REVISIONTREEWIDGET_H
