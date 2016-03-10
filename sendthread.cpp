#include "sendthread.h"
#include <QtNetwork>

sendThread::sendThread(int socketDescriptor, const QString &path, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), filePath(path)
{
    totalSize=0;
    remainSize=0;
    sendSize=0;
    packSize=128*1024;

}
void sendThread::run()
{
    newWindows=new QWidget();
    layout = new QGridLayout;
    progress = new QProgressBar;
    fileInfo=new QLabel;
    quit=new QPushButton("Quit");

    fileInfo->setText(filePath);
    progress->setMinimum(0);
    layout->addWidget(fileInfo);
    layout->addWidget(progress);
    layout->addWidget(quit,2,0,1,2,Qt::AlignRight);
    newWindows->setLayout(layout);
    newWindows->show();
    connect(quit,&QPushButton::clicked,newWindows,&QWidget::close);
    connect(this,&fileSize,progress,&QProgressBar::setMaximum);
    connect(this,&status,progress,&QProgressBar::setValue);

    tcpSocket=new QTcpSocket();
    qDebug()<<"This is run()";
    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket->error());
        return;
    }
    connect(tcpSocket,static_cast<void(QTcpSocket:: *)(qint64)>(&QTcpSocket::bytesWritten),
                                       this,&echo,Qt::DirectConnection);
//    connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(echo(qint64)),Qt::DirectConnection);
//    connect(tcpSocket,&QTcpSocket::bytesWritten,this,&sendThread,Qt::DirectConnection);
    readFile = new QFile(filePath);
    if(!readFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    fileName = filePath.right(filePath.size() - filePath.lastIndexOf('/')-1);
    totalSize=readFile->size();
    ///
    ///传输文件信息
    ///
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint64(0)<<quint64(0)<<fileName;
    totalSize+=block.size();
    out.device()->seek(0);
    out << totalSize << (quint64) (block.size() - sizeof(quint64)*2);
    remainSize=totalSize-(int)tcpSocket->write(block);
    block.resize(0);
    emit fileSize(totalSize);
    qDebug()<<"totalSize:"<<totalSize;
}

void sendThread::echo(qint64 sended)//传输文件
{
    sendSize+=sended;
    emit status(sendSize);//Update progress
    qDebug()<<"sendSize:"<<sendSize;
    if(sendSize>0)
    {
        block = readFile->read(qMin(remainSize,packSize));
        tcpSocket->write(block);
        remainSize-=block.size();
        block.resize(0);
    }
    else
        readFile->close();
    if(sendSize==totalSize)
    {
        qDebug()<<"Send file seccessfull!";
        readFile->close();
        tcpSocket->disconnectFromHost();
        tcpSocket->waitForDisconnected();
    }
}
