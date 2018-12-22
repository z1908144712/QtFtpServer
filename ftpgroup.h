#ifndef FTPGROUP_H
#define FTPGROUP_H

#include <QString>


class FtpGroup
{
public:
    FtpGroup();
    FtpGroup(QString name,QString path,QString file,QString directory);
    FtpGroup(int id,QString name,int count,QString path,QString file,QString directory);
    int getId();
    void setName(QString name);
    QString getName();
    void setCount(int count);
    int getCount();
    void setPath(QString path);
    QString getPath();
    void setFile(QString file);
    QString getFile();
    void setDirectory(QString directory);
    QString getDirectory();

private:
    int id;
    QString name;
    int count;
    QString path;
    QString file;
    QString directory;

};

#endif // FTPGROUP_H
