#include "ftpserver.h"
#include "sslserver.h"

#include <QDebug>
#include <QNetworkInterface>
#include <QHostInfo>


FtpServer::FtpServer(QObject *parent,int port,bool onlyOneIpAllowed,LogPrint *logPrint,QStatusBar *statusBar,FtpSqlConnection *sqlConnection) :
    QObject(parent)
{
    this->port=port;
    this->onlyOneIpAllowed = onlyOneIpAllowed;
    this->logPrint=logPrint;
    this->statusBar=statusBar;
    this->sqlConnection=sqlConnection;
    server = new SslServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(startNewControlConnection()));
}

FtpServer::~FtpServer(){
    statusBar->showMessage("");
}

void FtpServer::start(){
    server->listen(QHostAddress::AnyIPv4, port);
}

void FtpServer::stop(){
    server->close();
    for(int i=0;i<ftpControlConnections.length();i++){
        delete ftpControlConnections.at(i);
    }
}

bool FtpServer::isListening()
{
    return server->isListening();
}

QList<QString> FtpServer::lanIp()
{
    QList<QString> ips;
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        if(interface.flags().testFlag(QNetworkInterface::IsUp)&&interface.flags().testFlag(QNetworkInterface::IsRunning)&&!interface.flags().testFlag(QNetworkInterface::IsLoopBack)){
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();
            QNetworkAddressEntry entry=entryList.last();
            ips.append(entry.ip().toString());
        }
    }
    return ips;
}

void FtpServer::startNewControlConnection()
{
    QSslSocket *socket = (QSslSocket *) server->nextPendingConnection();

    // If this is not a previously encountered IP emit the newPeerIp signal.
    QString peerIp = socket->peerAddress().toString();
    logPrint->setText("connection from "+peerIp);
    logPrint->print();
    if (!encounteredIps.contains(peerIp)) {
        // If we don't allow more than one IP for the client, we close
        // that connection.
        if (onlyOneIpAllowed && !encounteredIps.isEmpty()) {
            delete socket;
            return;
        }

        emit newPeerIp(peerIp);
        encounteredIps.insert(peerIp);
    }

    // Create a new FTP control connection on this socket.
    FtpControlConnection *ftpControlConnection=new FtpControlConnection(this, socket, logPrint,sqlConnection);
    connect(ftpControlConnection,SIGNAL(close(FtpControlConnection*)),this,SLOT(deleteControlConnection(FtpControlConnection*)));
    ftpControlConnections.append(ftpControlConnection);
    statusBar->showMessage("当前用户数 "+QString::number(ftpControlConnections.length()));
}

void FtpServer::deleteControlConnection(FtpControlConnection* ftpControlConnection){
    ftpControlConnections.removeOne(ftpControlConnection);
    statusBar->showMessage("当前用户数 "+QString::number(ftpControlConnections.length()));
}

