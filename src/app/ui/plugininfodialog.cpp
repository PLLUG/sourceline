#include "plugininfodialog.h"
#include "ui_plugininfodialog.h"

PluginInfoDialog::PluginInfoDialog(QWidget *parent) :
    QDialog(parent,
            Qt::WindowSystemMenuHint
          | Qt::WindowTitleHint
          | Qt::WindowCloseButtonHint),
    ui(new Ui::PluginInfoDialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0, 2, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Category")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Info")));

    ui->tableView->setModel(model);

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
    QList <QStandardItem *> lItems;

    while (i.hasNext())
    {
        i.next();
        lItems.append(new QStandardItem(i.key()));
        lItems.append(new QStandardItem(i.value()));
        model->appendRow(lItems);
        lItems.clear();
    }

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PluginInfoDialog::on_okButton_clicked()
{
    close();
}
