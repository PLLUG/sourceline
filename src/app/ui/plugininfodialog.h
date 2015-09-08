#ifndef PLUGININFODIALOG_H
#define PLUGININFODIALOG_H

#include <QDialog>
#include <QString>

class QStandardItemModel;

namespace Ui {
class PluginInfoDialog;
}

/*!
 * \brief The PluginInfoDialog class implements dialog for displaying additional information
 *  about plugin. Dialog should be modal (does not allow user to interact with application, until it
 *  will be closed). Dialog will show additional information about plugin when user will press "i"
 *  button in PluginSettings dialog.
 */
class PluginInfoDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief Public constructor.
     */
    explicit PluginInfoDialog(QWidget *parent = 0);

    ~PluginInfoDialog();

    /*!
     * \brief Sets plugin name for which info dialog will be shown. Dialog will
     *  show name of the plugin in the title (example: "Plugin Info: <plugin name>")
     * \param pPluginName Name of the plugin.
     */
    void setPluginName(const QString &pPluginName = "UNDEFINED");

    /*!
     * \brief Sets hash containing information about plugin. Keys of hash should contain information
     *  field name (e.g. Author, Year, License, etc). Values contains actual value for each
     *  key (e.g "John" for Autor field, "GPLv3" for License etc).
     * \param pinfoHash Hash with plugin information.
     */
    void setPluginInfo(const QHash<QString, QString> &pInfoHash);

private:
    Ui::PluginInfoDialog *ui;

    QStandardItemModel *mModel;
    QString mWindowTitle;
};

#endif // PLUGININFODIALOG_H
