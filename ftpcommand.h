#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H

#include <QObject>

class QSslSocket;

class FtpCommand:public QObject
{
    Q_OBJECT
public:
    explicit FtpCommand(QObject *parent=0);
    void start(QSslSocket *socket);
protected:
    virtual void startImplementation()=0;
    QSslSocket* socket;
    bool started;
signals:
    void reply(const QString &details);
};

#endif // FTPCOMMAND_H
