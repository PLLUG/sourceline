#include "viewsettings.h"
#include "ui_viewsettings.h"

ViewSettings::ViewSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewSettings)
{
    ui->setupUi(this);
}

ViewSettings::~ViewSettings()
{
    delete ui;
}

void ViewSettings::on_cancelButton_clicked()
{
    this->close();
}

bool ViewSettings::isFileViewVisible() const
{
 return ui->FileView->isChecked();
}
void ViewSettings::setFileViewVisible(bool pShow)
{
 ui->FileView->setChecked(pShow);
}

bool ViewSettings::isRevisionTableVisible() const
{
 return ui->RevisionTable->isChecked();
}
void ViewSettings::setRevisionTableVisible(bool pShow)
{
 ui->RevisionTable->setChecked(pShow);
}

bool ViewSettings::isConsoleVisible() const
{
 return ui->Console->isChecked();
}
void ViewSettings::setConsoleVisible(bool pShow)
{
 ui->Console->setChecked(pShow);
}

bool ViewSettings::isEditorViewVisible() const
{
 return ui->EditorView->isChecked();
}
void ViewSettings::setEditorViewVisible(bool pShow)
{
 ui->EditorView->setChecked(pShow);
}

bool ViewSettings::isHistoryTreeVisible() const
{
 return ui->HistoryTree->isChecked();
}
void ViewSettings::setHistoryTreeVisible(bool pShow)
{
 ui->HistoryTree->setChecked(pShow);
}
