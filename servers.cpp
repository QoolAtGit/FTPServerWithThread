#include "servers.h"
#include "sendthread.h"
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QProgressBar>

Servers::Servers(QObject *parent)
    : QTcpServer(parent)
{
    filePath="G:/Code/Qt/tr.txt";
}
void Servers::incomingConnection(qintptr socketDescriptor)
{
    sendThread *thread = new sendThread(socketDescriptor, filePath, this);
    QWidget *newWindows=new QWidget();
    QGridLayout *layout = new QGridLayout;
    QProgressBar *progress = new QProgressBar;
    QLabel *fileInfo=new QLabel;
    QPushButton *quit=new QPushButton("Quit");
    fileInfo->setText(filePath);
    progress->setMinimum(0);
    layout->addWidget(fileInfo);
    layout->addWidget(progress);
    layout->addWidget(quit,2,0,1,2,Qt::AlignRight);
    newWindows->setLayout(layout);
    newWindows->show();
    connect(quit,&QPushButton::clicked,newWindows,&QWidget::close);
    connect(thread,&sendThread::fileSize,progress,&QProgressBar::setMaximum);
    connect(thread,&sendThread::status,progress,&QProgressBar::setValue);
    connect(thread,&sendThread::finished,thread,&sendThread::deleteLater);
    thread->start();
}
void Servers::setFilePath(QString Path)
{
    filePath=Path;
}
