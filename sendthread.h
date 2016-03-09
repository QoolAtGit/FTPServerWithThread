#ifndef SENDTHREAD
#define SENDTHREAD

#include <QThread>
#include <QTcpSocket>
#include <QFile>
class sendThread : public QThread
{
    Q_OBJECT

public:
    sendThread(int socketDescriptor, const QString &path, QObject *parent);

    void run() Q_DECL_OVERRIDE;

signals:
    void error(QTcpSocket::SocketError socketError);
    void status(qint64);
    void fileSize(qint64);

private:
    int socketDescriptor;
    QString filePath;
    QString fileName;
    QFile *readFile;
    qint64 totalSize;
    qint64 remainSize;
    qint64 sendSize;
};

#endif // SENDTHREAD

