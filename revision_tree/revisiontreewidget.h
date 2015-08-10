#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H

#include "revisionmodel.h"
#include <QWidget>


using IndexMap = std::map<vertex, int>;

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
    revision_graph mGraph;
    IndexMap mColumnMap;
    IndexMap mRowMap;
};

#endif // REVISIONTREEWIDGET_H
