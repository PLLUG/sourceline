#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QObject>
#include <QMap>

/*!
 * \brief The PageManager class handles all pages for repositories.
 */
class PageManager : public QObject
{
    Q_OBJECT
public:
    explicit PageManager(QObject *parent = 0);
    int getPageID();
    int getPageID(int);
    int getActiveIndex();
private:
     QMap<int, int> mPageHash;   //index, id

signals:
    /*!
     * \brief Emited when current page that corresponds to current selected repository tab is changed.
     * \param index Index of page.
     */
    void currentPageChanged(int index);
    void pageAdded(int index, QString name);
public slots:
    /*!
     * \brief Should be called  when current page that corresponds to current selected repository tab should be changed.
     * \param index Index of page.
     */
    void slotChangeCurrentPage(int index);
    void slotAddPage(QString lName);
    void slotRemovePage(int index);
    void slotTabMoved(int from, int to);
};

#endif // PAGEMANAGER_H
