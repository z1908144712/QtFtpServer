#ifndef FTPTHREAD_H
#define FTPTHREAD_H

#include <QThread>
#include "ftpserver.h"

class FtpThread:public QThread
{
    Q_OBJECT
public:
    FtpThread(QObject *parent, const QString &rootPath, int port, const QString &userName, const QString &password, bool readOnly, bool onlyOneIpAllowed);
    void run();
private:
    FtpServer *server;
    QObject *parent;
    QString rootPath;
    int port;
    QString userName;
    QString password;
    bool readOnly;
    bool onlyOneIpAllowed;
private slots:
    void onPeerIpChanged(const QString &peerIp);
};

#endif // FTPTREAD_H
