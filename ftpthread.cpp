#include "ftpthread.h"
#include <QDebug>

FtpThread::FtpThread(QObject *parent, const QString &rootPath, int port, const QString &userName, const QString &password, bool readOnly, bool onlyOneIpAllowed){
    this->parent=parent;
    this->rootPath=rootPath;
    this->port=port;
    this->userName=userName;
    this->password=password;
    this->readOnly=readOnly;
    this->onlyOneIpAllowed=onlyOneIpAllowed;
    server=new FtpServer(this,rootPath,port,userName,password,readOnly,onlyOneIpAllowed);
}

void FtpThread::run(){
    connect(server, SIGNAL(newPeerIp(QString)),this,SLOT(onPeerIpChanged(QString)));
    if (server->isListening()) {
        QString ips="";
        foreach (QString ip, FtpServer::lanIp()) {
            ips+=" "+ip+" ";
        }
        qDebug()<<"Listening at "<<ips.toUtf8();
    } else {
        qDebug()<<"Not listening";
    }
    this->exec();
}

void FtpThread::onPeerIpChanged(const QString &peerIp){
    qDebug()<<"Connected to "<<peerIp;
}
