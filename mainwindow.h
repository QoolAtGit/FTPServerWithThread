#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFileDialog>
#include <QGridLayout>
#include "servers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void sendMessages();

private slots:
    void on_OpenFileButton_clicked();

    void on_QuitButton_clicked();

private:
    Ui::MainWindow *ui;
    Servers tcpServer;
    /*
    QString fileName;
    QFile *readFile;
    qint64 totalSize;
    qint64 remainSize;
    qint64 sendSize;
        void OpenFile();
        void SendFile();
        QByteArray block;//用于暂存我们要发送的数据
        QTcpServer *tcpServer;
        QTcpSocket *clientConnect;
    public slots:
        void sendMessages();*/
};

#endif // MAINWINDOW_H
