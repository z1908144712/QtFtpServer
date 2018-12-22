#ifndef FTPSERVER_H
#define FTPSERVER_H

#include <QObject>
#include <QSet>
#include <QList>
#include <QStatusBar>
#include "logprint.h"

class SslServer;

// The ftp server. Listens on a port, and starts a new control connection each
// time it gets connected.

class FtpServer : public QObject
{
    Q_OBJECT
public:
    explicit FtpServer(QObject *parent,int port,bool onlyOneIpAllowed,LogPrint *logPrint,QStatusBar *statusBar);

    // Whether or not the server is listening for incoming connections. If it
    // is not currently listening then there was an error - probably no
    // internet connection is available, or the port address might require root
    // priviledges (on Linux).
    bool isListening();

    // Get the LAN IP of the host, e.g. "192.168.1.10".
    static QList<QString> lanIp();

    static int user_counter;

signals:
    // A connection from a new IP has been established. This signal is emitted
    // when the FTP server is connected by a new IP. The new IP will then be
    // stored and will not cause this FTP server instance to emit this signal
    // any more.
    void newPeerIp(const QString &ip);

private slots:
    // Called by the SSL server when we have received a new connection.
    void startNewControlConnection();

private:

    // The SSL server listen for incoming connections.
    SslServer *server;

    // All the IPs that this FTP server object has encountered in its lifetime.
    // See the signal newPeerIp.
    QSet<QString> encounteredIps;

    // Causes the server to remember the first IP that connects to it, and then
    // refuse connections from any other IP. This makes sense because a mobile
    // phone is unlikely to be used from 2 places at once.
    bool onlyOneIpAllowed;

    LogPrint *logPrint;

    QStatusBar *statusBar;


};

#endif // FTPSERVER_H
