#include "ftpserver.h"
#include "ftpcontrolconnection.h"
#include "sslserver.h"

#include <QDebug>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QSslSocket>

FtpServer::FtpServer(QObject *parent,int port,bool onlyOneIpAllowed,LogPrint *logPrint,QStatusBar *statusBar) :
    QObject(parent)
{
    server = new SslServer(this);
    // In Qt4, QHostAddress::Any listens for IPv4 connections only, but as of
    // Qt5, it now listens on all available interfaces, and
    // QHostAddress::AnyIPv4 needs to be used if we want only IPv4 connections.
#if QT_VERSION >= 0x050000
    server->listen(QHostAddress::AnyIPv4, port);
#else
    server->listen(QHostAddress::Any, port);
#endif
    connect(server, SIGNAL(newConnection()), this, SLOT(startNewControlConnection()));
    this->onlyOneIpAllowed = onlyOneIpAllowed;
    this->logPrint=logPrint;
    this->statusBar=statusBar;
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
    new FtpControlConnection(this, socket, logPrint,statusBar);
}
