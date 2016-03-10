#include "servers.h"
#include "sendthread.h"

Servers::Servers(QObject *parent)
    : QTcpServer(parent)
{
    filePath="G:/Code/Qt/tr.txt";
}
void Servers::incomingConnection(qintptr socketDescriptor)
{
    sendThread *thread = new sendThread(socketDescriptor, filePath, this);
    thread->start();/*
        connect(thread,&sendThread::fileSize,progress,&QProgressBar::setMaximum);
        connect(thread,&sendThread::status,progress,&QProgressBar::setValue);
        connect(thread,SIGNAL(fileSize(qint64)),progress,SLOT(setMaximum(qint64)));
        connect(thread,SIGNAL(status(qint64)),progress,SLOT(setValue(qint64)));*/
}
void Servers::setFilePath(QString Path)
{
    filePath=Path;
}
