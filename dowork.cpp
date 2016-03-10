#include "dowork.h"

dowork::dowork(int socketDescriptor, const QString &path):socketDescriptor(socketDescriptor), filePath(path)
{
    totalSize=0;
    remainSize=0;
    sendSize=0;
    packSize=128*1024;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        qDebug()<<tcpSocket.error();
        return;
    }
    connect(&tcpSocket,&QTcpSocket::bytesWritten,this,&missions);
}
void dowork::startSend()
{
    qDebug()<<"This is startSend()";
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
    remainSize=totalSize-(int)tcpSocket.write(block);
    block.resize(0);
    emit fileSize(totalSize);
    emit status(totalSize-remainSize);
    qDebug()<<"totalSize:"<<totalSize;
}

void dowork::missions(qint64 sended)
{
    qDebug()<<"This is missions()";
    sendSize+=sended;
    emit status(sendSize);//Update progress
    qDebug()<<"sendSize:"<<sendSize;
    if(sendSize>0)
    {
        block = readFile->read(qMin(remainSize,packSize));
        tcpSocket.write(block);
        remainSize-=block.size();
        block.resize(0);
        emit status(totalSize-remainSize);
    }
    else
        readFile->close();
    if(sendSize==totalSize)
    {
        qDebug()<<"Send file seccessfull!";
        readFile->close();
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        emit finish();
    }
}
