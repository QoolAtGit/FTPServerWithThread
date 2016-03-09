#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servers.h"

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

//    QWidget *qw = new QWidget;
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(0, 100);
    mainLayout->setColumnMinimumWidth(1, 10);
    mainLayout->setHorizontalSpacing(100);
    mainLayout->setVerticalSpacing(50);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 2);
    QLabel *label_Tea=new QLabel;
    label_Tea->setText("Hello Text!");
    mainLayout->addWidget(label_Tea,0,0,1,2);
//    ui->mainLayout->addWidget(ui->label_Title,0,0,1,1);
//    mainLayout->addWidget(ui->label_Port,3,0,1,1);
//    mainLayout->addWidget(ui->label_Messaga,2,0,1,2,Qt::AlignCenter);
    this->setLayout(mainLayout);
    this->show();

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
