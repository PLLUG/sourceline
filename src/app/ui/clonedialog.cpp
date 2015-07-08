#include "clonedialog.h"
#include "ui_clonedialog.h"

CloneDialog::CloneDialog(QWidget *parent):
    QDialog(parent,
            Qt::WindowSystemMenuHint
          | Qt::WindowTitleHint
          | Qt::WindowCloseButtonHint),
    ui(new Ui::CloneDialog)
{
    ui->setupUi(this);
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

CloneDialog::~CloneDialog()
{
    delete ui;
}

void CloneDialog::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        ui->cloneLineEdit->setText(directory);
    }
}

