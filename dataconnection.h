#ifndef DATACONNECTION_H
#define DATACONNECTION_H

#include "sslserver.h"
#include "QSslSocket"
#include "ftpcommand.h"

#include <QObject>
#include <QPointer>

class DataConnection:public QObject
{
    Q_OBJECT
public:
    explicit DataConnection(QObject *parent = 0);
    void scheduleConnectToHost(const QString &hostName, int port, bool encrypt);
    int listen(bool encrypt);
    bool setFtpCommand(FtpCommand *command);
    FtpCommand *ftpCommand();

private slots:
    void newConnection();
    void encrypted();
    void connected();

private:
    void startFtpCommand();
    SslServer *server;
    QSslSocket *socket;
    QPointer<FtpCommand> command;
    bool isSocketReady;
    bool isWaitingForFtpCommand;
    bool encrypt;

    bool isActiveConnection;
    QString hostName;
    int port;
};

#endif // DATACONNECTION_H
