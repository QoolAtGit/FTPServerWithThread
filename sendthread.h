#ifndef SENDTHREAD
#define SENDTHREAD

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QProgressBar>
class sendThread : public QThread
{
    Q_OBJECT

public:
    sendThread(int socketDescriptor, const QString &path, QObject *parent);

    void run() Q_DECL_OVERRIDE;
//public slots:
    void echo(qint64);

signals:
    void error(QTcpSocket::SocketError socketError);
    void status(qint64);
    void fileSize(qint64);

private:
    int socketDescriptor;
    QByteArray block;
    QFile *readFile;
    QString filePath;
    QString fileName;
    qint64 sendSize;
    qint64 packSize;
    qint64 totalSize;
    qint64 remainSize;
    QTcpSocket *tcpSocket;

    QWidget *newWindows;
    QGridLayout *layout;
    QProgressBar *progress;
    QLabel *fileInfo;
    QPushButton *quit;

};

#endif // SENDTHREAD

