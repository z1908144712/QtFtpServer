#include "ftpuser.h"

/*
 * FtpUser对应ftpuser
*/

/*
 * 空的构造方法
*/
FtpUser::FtpUser(){
    this->id=0;
    this->name="";
    this->password="";
    this->ftpgroup=0;
    this->path="";
    this->file="";
    this->directory="";
}

/*
 * 插入使用构造方法
*/
FtpUser::FtpUser(QString name,QString password,int ftpgroup,QString path,QString file,QString directory){
    this->name=name;
    this->password=password;
    this->ftpgroup=ftpgroup;
    this->path=path;
    this->file=file;
    this->directory=directory;
}

/*
 * 查询使用构造方法
*/
FtpUser::FtpUser(int id, QString name, QString password, int ftpgroup, QString path, QString file, QString directory){
    this->id=id;
    this->name=name;
    this->password=password;
    this->ftpgroup=ftpgroup;
    this->path=path;
    this->file=file;
    this->directory=directory;
}

/*
 * getter and setter 方法
*/
int FtpUser::getId(){
    return id;
}

QString FtpUser::getName(){
    return name;
}

void FtpUser::setName(QString name){
    this->name=name;
}

QString FtpUser::getPassword(){
    return password;
}

void FtpUser::setPassword(QString password){
    this->password=password;
}

int FtpUser::getFtpGroup(){
    return ftpgroup;
}

void FtpUser::setFtpGroup(int ftpgroup){
    this->ftpgroup=ftpgroup;
}

QString FtpUser::getPath(){
    return path;
}

void FtpUser::setPath(QString path){
    this->path=path;
}

QString FtpUser::getFile(){
    return file;
}

void FtpUser::setFile(QString file){
    this->file=file;
}

QString FtpUser::getDirectory(){
    return directory;
}

void FtpUser::setDirectory(QString directory){
    this->directory=directory;
}
