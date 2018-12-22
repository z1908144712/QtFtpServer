#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>

class QSslSocket;

class SslServer:public QTcpServer
{
    Q_OBJECT
public:
    explicit SslServer(QObject *parent);
    static void setLocalCertificateAndPrivateKey(QSslSocket *socket);

private:
#if QT_VERSION >= 0x050000
    typedef qintptr PortableSocketDescriptorType;
#else
    typedef int PortableSocketDescriptorType;
#endif

    void incomingConnection(PortableSocketDescriptorType socketDescriptor);
};

#endif // SSLSERVER_H
