#ifndef SERVERS
#define SERVERS

#include <QTcpServer>

class Servers : public QTcpServer
{
    Q_OBJECT

public:
    Servers(QObject *parent = 0);
    void setFilePath(QString filePath);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    QString filePath;
    //    qintptr<QList> serverList;
};

#endif // SERVERS

