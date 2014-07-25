#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include <QDialog>
#include <QDockWidget>
namespace Ui {
class ViewSettings;
}

class ViewSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ViewSettings(QWidget *parent = 0);
    ~ViewSettings();
    bool isFileViewVisible() const;
    void setFileViewVisible(bool pShow);

    bool isRevisionTableVisible() const;
    void setRevisionTableVisible(bool pShow);

    bool isConsoleVisible() const;
    void setConsoleVisible(bool pShow);

    bool isHistoryTreeVisible() const;
    void setHistoryTreeVisible(bool pShow);

    bool isEditorViewVisible() const;
    void setEditorViewVisible(bool pShow);
private slots:
    void on_cancelButton_clicked();

private:
    Ui::ViewSettings *ui;

};
#endif // VIEWSETTINGS_H
