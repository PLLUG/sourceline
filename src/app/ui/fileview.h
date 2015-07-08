#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>

namespace Ui {
    class FileView;
}

class QMenu;
class QFileSystemModel;

class FileView : public QWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = 0);
    ~FileView();
    void setRootPath(const QString pPath);
    QString currentRootPath() const;

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void slotDoubleClick(const QModelIndex &index);
    void slotGoUp();
    void slotRightBtnClick(const QPoint &pos);

private:
    Ui::FileView *ui;
    QMenu *mMenu;
    QMenu *mFileMenu;
    QMenu *mDirMenu;
    QString mRootPath;
    QFileSystemModel *mFileModel;
};

#endif // FILEVIEW_H
