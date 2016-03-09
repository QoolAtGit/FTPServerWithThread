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
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
void Servers::setFilePath(QString Path)
{
    filePath=Path;
}
