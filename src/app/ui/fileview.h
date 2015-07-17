#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>

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
    void setRootPath(const QString &pPath);

    /*!
     * \brief set root path in different platforms
     * \return path
     */
    static QString setHomePath()
    {
        QString rHomePath;
        #ifdef Q_OS_LINUX
        rHomePath = "/";
        #endif
        #ifdef Q_OS_WIN
        rHomePath = "My Computer";
        #endif
        #ifdef Q_OS_MAC
        rHomePath = "/";
        #endif
        return rHomePath;
    }

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
     * \brief file model
     */
    QFileSystemModel *mFileModel;
};

#endif // FILEVIEW_H
