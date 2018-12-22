#ifndef FTPCRYPTO_H
#define FTPCRYPTO_H

#include <QString>

class FtpCrypto
{
public:
    FtpCrypto();
    static QString cryptopassword(QString password);
};

#endif // FTPCRYPTO_H
