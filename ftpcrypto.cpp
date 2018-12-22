#include "ftpcrypto.h"

#include <QCryptographicHash>
#include <QByteArray>

/*
 * FtpCrypto用于求哈希
*/

FtpCrypto::FtpCrypto()
{

}

/*
 * 使用SHA256加密字符串
 * @return QString
*/
QString FtpCrypto::cryptopassword(QString password){
    QByteArray byte_array;
    byte_array.append(password);
    QByteArray hash_byte_array=QCryptographicHash::hash(byte_array,QCryptographicHash::Sha256);
    return hash_byte_array.toHex();
}
