#ifndef TABSAPI_H
#define TABSAPI_H

#include <QWidget>
#include <QObject>

class CustomTabBar;

/*!
 * \brief The PageManager class handles all pages for repositories.
 */
class TabsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TabsAPI(QObject *parent = 0);
    /*!
     * \brief Get current index of tab
     * \param pTabBar - tabBar where is this tab
     * \return index current tab
     */
    int getCurrentIndex(CustomTabBar *pTabBar);
    /*!
     * \brief get count tabs
     * \param pTabBar - tab bar
     * \return amount tabs
     */
    int getCountTabs(CustomTabBar *pTabBar);

    /*!
     * \brief Get widget of current tab
     * \param pTabBar
     * \return Returns a pointer to the page currently being displayed by the tab dialog.
     */
    QWidget* getCurrentWidget(CustomTabBar *pTabBar);

    /*!
     * \brief Get widget of tab with index
     * \param pTabBar
     * \param index of tab
     * \return Returns the tab page at index position index
     */
    QWidget* getWidget(CustomTabBar *pTabBar, int pIndex);

public slots:
    /*!
     * \brief Add New Workplace in main menu
     * \param lName Name of tab
     */
    void slotAddNewWorkplace(CustomTabBar *pTabBar, const QString &pName);
};

#endif // TABSAPI_H
