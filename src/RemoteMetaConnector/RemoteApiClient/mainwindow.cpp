

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mInterface(new TextEditInterface(this)),
    mRemoteClient(new RemoteApiClient(this))
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::slotSetText, Qt::UniqueConnection);
    connect(mInterface, &TextEditInterface::invoked, mRemoteClient, &RemoteApiClient::slotInvoke, Qt::UniqueConnection);
    mRemoteClient->connectToProvider("sl");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSetText()
{
    mInterface->setText(ui->plainTextEdit->toPlainText());
}
