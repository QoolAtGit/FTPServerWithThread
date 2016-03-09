#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servers.h"
#include <QtNetwork>
#include <QFileDialog>
#include <QGridLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString info="Available IP addresses:\n";
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for(int i=0;i<ipAddressesList.size(); ++i)
    {

        if (ipAddressesList.at(i).toIPv4Address())
        {
            info.append('\n'+ipAddressesList.at(i).toString());
        }
    }
    ui->label_Title->setText(info);
    ui->label_Port->setText("Server port:10801");
    ui->label_Messaga->setText("File to be sended:\nG:/Code/Qt/tr.txt");

    QGridLayout *mainLayout = new QGridLayout();
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(ui->OpenFileButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(ui->QuitButton, QDialogButtonBox::RejectRole);
    mainLayout->addWidget(ui->label_Title,0,0);
    mainLayout->addWidget(ui->label_Port,1,0);
    mainLayout->addWidget(ui->label_Messaga,2,0,1,2);
    mainLayout->addWidget(buttonBox, 3, 0, 1,2);
    QWidget* widget = new QWidget(this);
    widget->setLayout(mainLayout);
    this->setCentralWidget(widget);

    if( !tcpServer.listen(QHostAddress::Any, 10801) )
    {
        qDebug() << tcpServer.errorString();
        close();
    }
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty())
    {
        qDebug()<<"File "<<filePath<<" open successfull!";
    }
    else
        return;
    tcpServer.setFilePath(filePath);
    ui->label_Messaga->setText(tr("File to be sended:\n%1").arg(filePath));
}

void MainWindow::on_QuitButton_clicked()
{
    close();
}
