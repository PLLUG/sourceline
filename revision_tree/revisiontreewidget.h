#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
#include <QOpenGLWidget>

#include "revisionmodel.h"

/*!
 * \brief The RevisionTreeWidget class Paints revision graph
 */
class RevisionTreeWidget : public QOpenGLWidget
{
public:
    RevisionTreeWidget(QWidget* parent = nullptr);

    void setGraph(const revision_graph &pGraph);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;

private:
    revision_graph mGraph;
};

#endif // REVISIONTREEWIDGET_H
