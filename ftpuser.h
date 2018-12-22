#ifndef FTPUSER_H
#define FTPUSER_H

#include <QString>

class FtpUser
{
public:
    FtpUser();
    FtpUser(QString name,QString password,int ftpgroup,QString path,QString file,QString directory);
    FtpUser(int id,QString name,QString password,int ftpgroup,QString path,QString file,QString directory);
    int getId();
    void setName(QString name);
    QString getName();
    void setPassword(QString password);
    QString getPassword();
    void setFtpGroup(int ftpgroup);
    int getFtpGroup();
    void setPath(QString path);
    QString getPath();
    void setFile(QString file);
    QString getFile();
    void setDirectory(QString directory);
    QString getDirectory();
private:
    int id;
    QString name;
    QString password;
    int ftpgroup;
    QString path;
    QString file;
    QString directory;
};

#endif // FTPUSER_H
