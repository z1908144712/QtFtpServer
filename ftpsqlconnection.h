#ifndef FTPSQLCONNECTION_H
#define FTPSQLCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QMap>
#include "ftpuser.h"
#include "ftpgroup.h"

class FtpSqlConnection
{
public:
    FtpSqlConnection(QString path,QString username,QString password);
    ~FtpSqlConnection();
    bool insertGroup(FtpGroup group);
    bool hasGroupByName(QString name);
    bool insertUser(FtpUser user);
    bool updateUserBasic(FtpUser ftpUser);
    bool updateUserFileAccess(int id,QString file);
    bool updateUserDirAccess(int id,QString dir);
    bool updateUserFileAndDirAccess(int id,QString file,QString dir);
    bool updateGroupBasic(FtpGroup group);//修改组的基本信息
    bool updateGroupFileAccess(int id,QString file);//修改组的权限信息
    bool updateGroupDirAccess(int id,QString dir);
    bool updateGroupFileAndDirAccess(int id,QString file,QString dir);
    bool hasUserByName(QString name);
    bool deleteUserById(int id);
    bool deleteGroupById(int id);
    QString queryGroupNameById(int id);
    QString queryGroupPathByName(QString name);
    int queryGroupIdByName(QString name);
    FtpUser queryUserByName(QString name);
    FtpUser queryUserById(int id);
    FtpGroup queryGroupByName(QString name);
    FtpGroup queryGroupById(int id);
    QList<QMap<QString,QString>> listGroupNames();
    QList<QMap<QString,QString>> listUserNames();
private:
    QSqlDatabase database;
};

#endif // FTPSQLCONNECTION_H
