#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ftpserver.h"
#include "logprint.h"
#include "ftpsqlconnection.h"
#include "setusergroupwindow.h"
#include "ftpabout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void start();
    void stop();

private:
    Ui::MainWindow *ui;
    FtpServer *server;
    LogPrint *logPrint;
    SetUserGroupWindow *setUserGroupWindow;
    FtpAbout *ftpAbout;
    FtpSqlConnection *sqlConnection;

    void startServer();
    void stopServer();

private slots:
    void onPeerIpChanged(const QString &peerIp);
    void trigerMenu(QAction*);
};

#endif // MAINWINDOW_H
