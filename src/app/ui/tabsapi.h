#ifndef TABSAPI_H
#define TABSAPI_H

#include <QObject>
#include <QMap>

/*!
 * \brief The PageManager class handles all pages for repositories.
 */
class TabsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TabsAPI(QObject *parent = 0);
    int getTabID();
    int getTabID(int);
    int getActiveIndex();
private:
     QMap<int, int> mTabHash;   //index, id

signals:
    /*!
     * \brief Emited when current page that corresponds to current selected repository tab is changed.
     * \param index Index of page.
     */
    void currentWorkplaceChanged(int index);
    /*!
     * \brief Emited when new workplace was added in main menu
     * \param index Index of page.
     * \param name Name of tab
     */
    void newWorkplaceAdded(int index, QString name);
public slots:
    /*!
     * \brief Should be called  when current page that corresponds to current selected repository tab should be changed.
     * \param index Index of page.
     */
    void slotChangeCurrentTab(int index);
    /*!
     * \brief Add New Workplace in main menu
     * \param lName Name of tab
     */
    void slotAddNewWorkplace(QString lName);
    /*!
     * \brief Remove workplace with given index
     * \param index of tab
     */
    void slotRemoveWorkplace(int index);
    /*!
     * \brief Moved Tab from one position to another
     * \param from old position(index)
     * \param to new position(index)
     */
    void slotTabMoved(int from, int to);
};

#endif // TABSAPI_H
