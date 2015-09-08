#include "plugininfodialog.h"
#include "ui_plugininfodialog.h"

#include <QStandardItemModel>
#include <QStandardItem>

PluginInfoDialog::PluginInfoDialog(QWidget *parent) :
    QDialog(parent,
            Qt::WindowSystemMenuHint
            | Qt::WindowTitleHint
            | Qt::WindowCloseButtonHint),
    ui(new Ui::PluginInfoDialog)
{
    ui->setupUi(this);

    mModel = new QStandardItemModel(0, 2, this);
    mModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Category")));
    mModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Info")));

    ui->tableView->setModel(mModel);

    mWindowTitle = "Plugin Info: %1";
    setPluginName();

    QString lStyleSheet = QString("QHeaderView::section {")
            + "background-color: #A9A9A9;"
            // + "font-weight: bold;"
            // + "border: 1px solid #808080;"
            + "}";

    ui->tableView->setStyleSheet(lStyleSheet);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);
}

PluginInfoDialog::~PluginInfoDialog()
{
    delete ui;
}

void PluginInfoDialog::setPluginName(const QString &pPluginName)
{
    setWindowTitle(mWindowTitle.arg(pPluginName));
}

void PluginInfoDialog::setPluginInfo(const QHash<QString, QString> &pInfoHash)
{
    QHashIterator <QString, QString> i(pInfoHash);
    while (i.hasNext())
    {
        i.next();
        mModel->appendRow(QList <QStandardItem *>()
                          << new QStandardItem(i.key()) << new QStandardItem(i.value()));
    }
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
