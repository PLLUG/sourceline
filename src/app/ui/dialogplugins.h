#ifndef DIALOGPLUGINS_H
#define DIALOGPLUGINS_H
#include "../pluginsupport/plugininfo.h"
#include <QList>
#include <QString>
#include <QDialog>
#include <QMap>
#include <QStringList>
class QSignalMapper;

class QTreeWidgetItem;

namespace Ui {
    class DialogPlugins;
}

class DialogPlugins : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPlugins(QWidget *parent = 0);
    ~DialogPlugins();
    /*!
     * \brief Adds plugin to list and all necessary information about it
     * \param pPluginInfo object which include description about plugin
     */
    void addPluginInfo(const PluginInfo& pPluginInfo);
    /*!
     * \brief Returns plugins description(used when user clicks on info button in row with plugin description).
     * \param pluginId Plugin identifier, for which info button was pressed.
     */
    QString requestInfoForPlugin(QString pPluginId);
    /*!
     * \brief  get information about plugins fron files
     * \return dictionary where key word is plugin category and value is object which include description about plugin
     */
    void setPlugins(QList<PluginInfo> pPlugins);
    /*!
     * \brief Returns plugins that was enabled by user. Returns valid value after dialog execution.
     * \return List of active plugin identifiers.
     */
    QStringList activePlugins();
    /*!
     * \brief Shows when user wants to restart application to immediately appy all changes.
     *  Returns valid value after dialog execution.
     * \
     * return True if restart; false otherwise
     */
    bool restartApplication();
    void setActivatedPlugins(QList<QString> pActivatedPlugins);
private slots:
    /*!
     * \brief Shows plugins when when user clicks on info button in row with plugin description
     * \param pluginId Plugin identifier, for which info button was pressed.
     */
    void slotButtonPressed(QString pPluginId);
    /*!
     * \brief Change mIsApplyAndRestartPressed to true.
     */
    void slotApplyAndRestartPressed();
private:
    /*!
     * \brief create Plugins ui
     * \param pPlugins is plugin description
     */
    void createPluginsTree();
    /*!
     * \brief add plugin category into Plugins Tree
     * \param pCategory plugin Category. Plugins with the same categories are grouped together.
     * \param pName is plugin unique id
     * \param pVer is plugin version
     * \param pDescr is plugin short description
     */
    void addCategory(const QString& pCategory, const QString& pPluginId, const QString &pVer, const QString &pDescr);
    /*!
     * \brief add plugin into subtre QTreeWidgetItem which describe just category
     * \param pParent is QTreeWidgetItem which have the same categoty as plugin
     * \param pName is plugin unique id
     * \param pVer is plugin version
     * \param pDescr is plugin short description
     */
    void addPluginToCategory(QTreeWidgetItem *pParent, const QString& pPluginId, const QString &pVer, const  QString &pDescr);
    /*!
     * \brief function creates button for ui part.
     * \param pPluginItem is QTreeWidgetItem which include info about plugin in row in Plugin tree
     * \return pointer to button widget which will be in row with plugin description
     */
    QWidget* createButton(QTreeWidgetItem* pPluginItem);
private:
    Ui::DialogPlugins *ui;
    QSignalMapper *mMapper;
    bool mIsApplyAndRestartPressed;
    QList<PluginInfo> mPlugins;
};

#endif // DIALOGPLUGINS_H
