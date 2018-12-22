#include "ftpcommand.h"

#include <QSslSocket>

FtpCommand::FtpCommand(QObject *parent):
    QObject(parent)
{
    started=false;
}

void FtpCommand::start(QSslSocket *socket){
    started=true;
    this->socket=socket;
    this->socket->setParent(this);
    connect(this->socket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    startImplementation();
}
