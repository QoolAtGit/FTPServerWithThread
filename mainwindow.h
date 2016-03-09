#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_OpenFileButton_clicked();

    void on_QuitButton_clicked();

private:
    Ui::MainWindow *ui;
    Servers tcpServer;
};

#endif // MAINWINDOW_H
