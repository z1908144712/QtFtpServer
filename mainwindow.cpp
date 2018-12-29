#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>

/*
 * 主界面
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    sqlConnection=new FtpSqlConnection("access.db","","");
    ui->setupUi(this);
    logPrint=new LogPrint(ui->textEdit);
    startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 监听菜单栏
*/
void MainWindow::trigerMenu(QAction* action){
    if(action==ui->actionSetUserGroup){
        setUserGroupWindow=new SetUserGroupWindow(this,sqlConnection);
        setUserGroupWindow->exec();
    }else if(action==ui->actionAbout){
        ftpAbout=new FtpAbout(this);
        ftpAbout->exec();
    }else if(action==ui->actionStart){
        startServer();
    }else if(action==ui->actionStop){
        stopServer();
    }
}

/*
 * 打印连接信息
*/
void MainWindow::onPeerIpChanged(const QString &peerIp)
{
    logPrint->setText("Connected to " + peerIp);
    logPrint->print();
}

/*
 * 启动服务
*/
void MainWindow::startServer(){
    server=new FtpServer(this,21,false,logPrint,ui->statusBar,sqlConnection);
    if (server->isListening()) {
        ui->actionStart->setEnabled(false);
        ui->actionStop->setEnabled(true);
        connect(server, SIGNAL(newPeerIp(QString)),this,SLOT(onPeerIpChanged(QString)));
        connect(ui->menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));
        QString ips=" (";
        foreach (QString ip, FtpServer::lanIp()) {
            ips+=" "+ip+" ";
        }
        ips+=")";
        logPrint->setText("Server started! Listening at"+ips);
        logPrint->print();
    } else {
        delete server;
        ui->actionStart->setEnabled(true);
        ui->actionStop->setEnabled(false);
        logPrint->setText("Server start failed!");
        logPrint->print();
    }
}

/*
 * 关闭服务
*/
void MainWindow::stopServer(){
    delete server;
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);
    logPrint->setText("Server stoped!");
    logPrint->print();
}
