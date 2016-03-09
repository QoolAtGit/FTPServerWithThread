#include "sendthread.h"
#include <QtNetwork>

sendThread::sendThread(int socketDescriptor, const QString &path, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), filePath(path)
{
    totalSize=0;
    remainSize=0;
    sendSize=128*1024;
}
void sendThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket.error());
        return;
    }

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
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint64(0)<<quint64(0)<<fileName;
    totalSize+=block.size();
    out.device()->seek(0);
    out << totalSize << (quint64) (block.size() - sizeof(quint64)*2);
    remainSize=totalSize-(int)tcpSocket.write(block);
    block.resize(0);

    qDebug()<<"totalSize:"<<totalSize;

    ///
    ///传输文件
    ///
    while(remainSize>0)
    {
        qDebug()<<"Remaining size:"<<remainSize;
        block = readFile->read(qMin(remainSize,sendSize));
        tcpSocket.write(block);
        remainSize-=block.size();
        block.resize(0);
    }
    if(remainSize<=0)
    {
        qDebug()<<"Send file seccessfull!";
        readFile->close();
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
    }
}
