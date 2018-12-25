#include "ftpsqlconnection.h"
#include <QDebug>

/*
 * FtpSqlConnection包含所有数据库的操作
*/
FtpSqlConnection::FtpSqlConnection(QString path,QString username,QString password)
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.setUserName(username);
    database.setPassword(password);
    if(!database.open()){
        qDebug()<<"Error: Failed to connect database."<<database.lastError();
    }else{
        qDebug()<<"Succeed to connect database.";
    }
}

FtpSqlConnection::~FtpSqlConnection(){
    database.close();
}

/*
 * 根据name判断在ftpgroup表中是否已存在
 * @return bool
*/
bool FtpSqlConnection::hasGroupByName(QString name){
    QString sql="select * from ftpgroup where name=:name;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",name);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return true;
    }else{
        if(sqlQuery.next()){
            return true;
        }else{
            return false;
        }
    }
}

/*
 * 根据name判断在ftpuser表中是否已存在
 * @return bool
*/
bool FtpSqlConnection::hasUserByName(QString name){
    QString sql="select * from ftpuser where name=:name;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",name);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return true;
    }else{
        if(sqlQuery.next()){
            return true;
        }else{
            return false;
        }
    }
}

/*
 * ftpuser插入数据
 * @return bool
*/
bool FtpSqlConnection::insertUser(FtpUser user){
    if(!hasUserByName(user.getName())){
        QString sql="insert into ftpuser(id,name,password,ftpgroup,path,file,directory) values(null,:name,:password,:ftpgroup,:path,:file,:directory);";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(sql);
        sqlQuery.bindValue(":name",user.getName());
        sqlQuery.bindValue(":password",user.getPassword());
        sqlQuery.bindValue(":ftpgroup",user.getFtpGroup());
        sqlQuery.bindValue(":path",user.getPath());
        sqlQuery.bindValue(":file",user.getFile());
        sqlQuery.bindValue(":directory",user.getDirectory());
        if(!sqlQuery.exec()){
            qDebug()<<sqlQuery.lastError();
            return false;
        }else{
            return true;
        }
    }
    return false;
}

/*
 * ftpgroup更新基本信息
 * @return bool
*/

bool FtpSqlConnection::updateGroupBasic(FtpGroup group){

    // update student set name = :name where id = :id";

     QString sql="update ftpgroup set name = :name, path= :path where id=:id;";
     QSqlQuery sqlQuery;
     sqlQuery.prepare(sql);
     sqlQuery.bindValue(":name",group.getName());
     sqlQuery.bindValue(":path",group.getPath());
     sqlQuery.bindValue(":id",group.getId());
     if(!sqlQuery.exec()){
         qDebug()<<sqlQuery.lastError();
         return false;
     }else{
         return true;
     }
}
/*
 * ftpgroup插入数据
 * @return bool
*/
bool FtpSqlConnection::insertGroup(FtpGroup group){
    if(!hasGroupByName(group.getName())){
        QString sql="insert into ftpgroup(id,name,count,path,file,directory) values(null,:name,:count,:path,:file,:directory);";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(sql);
        sqlQuery.bindValue(":name",group.getName());
        sqlQuery.bindValue(":count",group.getCount());
        sqlQuery.bindValue(":path",group.getPath());
        sqlQuery.bindValue(":file",group.getFile());
        sqlQuery.bindValue(":directory",group.getDirectory());
        if(!sqlQuery.exec()){
            qDebug()<<sqlQuery.lastError();
            return false;
        }else{
            return true;
        }
    }
    return false;
}

/*
 * 根据id从ftpuser删除数据
 * @return bool
*/
bool FtpSqlConnection::deleteUserById(int id){
    QString sql="delete from ftpuser where id=:id;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":id",id);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return false;
    }else{
        return true;
    }
}

/*
 * 根据id从ftpgroup删除数据
 * @return bool
*/
bool FtpSqlConnection:: deleteGroupById(int id){
    QString sql="delete from ftpgroup where id=:id;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":id",id);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return false;
    }else{
        return true;
    }
}

/*
 * 根据name从ftpuser查询数据
 * @return  FtpUser
*/
FtpUser FtpSqlConnection::queryUserByName(QString name){
    QString sql="select * from ftpuser where name=:name;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",name);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return FtpUser();
    }else{
        if(sqlQuery.next()){
            return FtpUser(sqlQuery.value(0).toInt(),sqlQuery.value(1).toString(),sqlQuery.value(2).toString(),sqlQuery.value(3).toInt(),sqlQuery.value(4).toString(),sqlQuery.value(5).toString(),sqlQuery.value(6).toString());
        }else{
            return FtpUser();
        }
    }
}

/*
 * 根据name从ftpgroup查询数据
 * @return  FtpGroup
*/
FtpGroup FtpSqlConnection::queryGroupByName(QString name){
    QString sql="select * from ftpgroup where name=:name;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",name);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return FtpGroup();
    }else{
        if(sqlQuery.next()){//存在的话，就返回用户组
            return FtpGroup(sqlQuery.value(0).toInt(),sqlQuery.value(1).toString(),sqlQuery.value(2).toInt(),sqlQuery.value(3).toString(),sqlQuery.value(4).toString(),sqlQuery.value(5).toString());
        }else{
            return FtpGroup();
        }
    }
}

/*
 * 根据id从ftpgroup查询数据
 * @return  FtpGroup
*/
FtpGroup FtpSqlConnection::queryGroupById(int id){
    QString sql="select * from ftpgroup where id=:id;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":id",id);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return FtpGroup();
    }else{
        if(sqlQuery.next()){
            return FtpGroup(sqlQuery.value(0).toInt(),sqlQuery.value(1).toString(),sqlQuery.value(2).toInt(),sqlQuery.value(3).toString(),sqlQuery.value(4).toString(),sqlQuery.value(5).toString());
        }else{
            qDebug()<<"id"<<id;
            return FtpGroup();
        }
    }
}

/*
 * 根据id从ftpgroup查询name
 * @return  QString
*/
QString FtpSqlConnection::queryGroupNameById(int id){
    QString sql="select name from ftpgroup where id=:id;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":id",id);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return "";
    }else{
        if(sqlQuery.next()){
            return sqlQuery.value(0).toString();
        }else{
            return "";
        }
    }
}

/*
 * 根据name从ftpgroup查询id
 * @return  int
*/
int FtpSqlConnection::queryGroupIdByName(QString name){
    QString sql="select id from ftpgroup where name=:name;";
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",name);
    if(!sqlQuery.exec()){
        qDebug()<<sqlQuery.lastError();
        return 0;
    }else{
        if(sqlQuery.next()){
            return sqlQuery.value(0).toInt();
        }else{
            return 0;
        }
    }
}

/*
 * 从ftpgroup查询全部的id,name
 * @return  QList<QMap<QString,QStirng>>
*/
QList<QMap<QString,QString>> FtpSqlConnection::listGroupNames(){
    QSqlQuery sqlQuery;
    QList<QMap<QString,QString>> list;
    if(!sqlQuery.exec("select id,name from ftpgroup;")){
        qDebug()<<sqlQuery.lastError();
    }else{
        while (sqlQuery.next()) {
            QMap<QString,QString> map;
            map.insert("id",sqlQuery.value(0).toString());
            map.insert("name",sqlQuery.value(1).toString());
            list.append(map);
        }
    }
    return list;
}

/*
 * 从ftpuser查询全部的id,name
 * @return  QList<QMap<QString,QStirng>>
*/
QList<QMap<QString,QString>> FtpSqlConnection::listUserNames(){
    QSqlQuery sqlQuery;
    QList<QMap<QString,QString>> list;
    if(!sqlQuery.exec("select id,name from ftpuser;")){
        qDebug()<<sqlQuery.lastError();
    }else{
        while (sqlQuery.next()) {
            QMap<QString,QString> map;
            map.insert("id",sqlQuery.value(0).toString());
            map.insert("name",sqlQuery.value(1).toString());
            list.append(map);
        }
    }
    return list;
}
