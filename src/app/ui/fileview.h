#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include "genericdockwidget.h"

namespace Ui {
    class FileView;
}

class QMenu;
class QFileSystemModel;

/*!
 * \brief The class for representation file view
 */
class FileView : public QWidget
{
    Q_OBJECT

public:

    explicit FileView(QWidget *parent = 0);
    ~FileView();

    /*!
     * \brief set root path for system
     * \param path which must be root
     */
    void setRootPath(const QString pPath);

    /*!
     * \brief current root path
     * \return root path
     */
    QString currentRootPath() const;

protected:

    /*!
     * \brief update icon position and size
     */
    void resizeEvent(QResizeEvent *);

private slots:

    /*!
     * \brief open folder on double click
     * \param index item in model
     */
    void slotDoubleClick(const QModelIndex &index);

    /*!
     * \brief go up to repository
     */
    void slotGoUp();

    /*!
     * \brief action create menu on right button click
     * \param position item on view
     */
    void slotRightBtnClick(const QPoint &pos);

    /*!
     * \brief create new folder
     */
    void slotCreateNewFolder();

    /*!
     * \brief delete folder
     */
    void slotDeleteFolder();

    /*!
     * \brief delete file
     */
    void slotDeleteFile();

    /*!
     * \brief rename rolder or file
     */
    void slotRenameFolderOrFile();

private:

    /*!
     * \brief user interface
     */
    Ui::FileView *ui;

    /*!
     * \brief main context menu
     */
    QMenu *mMenu;

    /*!
     * \brief context menu for file
     */
    QMenu *mFileMenu;

    /*!
     * \brief context menu for folders
     */
    QMenu *mDirMenu;

    /*!
     * \brief root path in system
     */
    QString mRootPath;

    /*!
     * \brief file model
     */
    QFileSystemModel *mFileModel;

};

#endif // FILEVIEW_H
