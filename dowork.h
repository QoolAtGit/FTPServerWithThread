#ifndef DOWORK_H
#define DOWORK_H

#include <QObject>
#include <QFile>
#include <QTcpSocket>
#include <QDataStream>

//class Worker : public QObject
//{
//Q_OBJECT
//public slots:
//    void doWork() {
//        /* ... */
//    }
//};

class dowork: public QObject
{
    Q_OBJECT
public:
    dowork(int socketDescriptor, const QString &path);
public slots:
    void missions(qint64);
    void startSend();
signals:
    void status(qint64);
    void fileSize(qint64);
    void finish();
private:
    int socketDescriptor;
    QString filePath;
    QString fileName;
    QFile *readFile;
    qint64 totalSize;
    qint64 remainSize;
    qint64 packSize;
    qint64 sendSize;
    QTcpSocket tcpSocket;
    QByteArray block;
};

#endif // DOWORK_H
