#ifndef GENERICDOCKWIDGET_H
#define GENERICDOCKWIDGET_H

#include <QDockWidget>

#include "guidefs.h"

/*!
 * \brief The GenericDockWidget class is base class for all dock widgets in application.
 */
class GenericDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit GenericDockWidget(QWidget *parent = 0);

    /*!
     * \brief Returns dock type. Appication will identify, where place this dock, usind its type.
     *  Also it could be used for checking what type of widgets dock contains.
     * \return Type of dock.
     */
    virtual DockType type() const = 0;

    /*!
     * \brief Adds page to dock.
     * \param pIndex Page number where place widget.
     * \param pWidget Widget that should be placed on page.
     */
    void addPage(int pIndex, QWidget *pWidget);

public slots:
    /*!
     * \brief Should be called when current page in application was changed.
     * \param pPage Current page that corresponds to current active repository tab in application.
     */
    void slotSetPage(int pPage);
};

#endif // GENERICDOCKWIDGET_H
