#include "ftpgroup.h"

/*
 * FtpGroup对应数据库的ftpgroup
*/

/*
 * 空的构造方法
*/
FtpGroup::FtpGroup(){
    this->id=0;
    this->name="";
    this->path="";
    this->file="";
    this->directory="";
}

/*
 * 插入数据使用构造方法
*/
FtpGroup::FtpGroup(QString name,QString path,QString file,QString directory){
    this->name=name;
    this->path=path;
    this->file=file;
    this->directory=directory;
}

/*
 * 查询数据使用构造方法
*/
FtpGroup::FtpGroup(int id, QString name,  QString path, QString file, QString directory){
    this->id=id;
    this->name=name;
    this->path=path;
    this->file=file;
    this->directory=directory;
}

/*
 * getter and setter 方法
*/
int FtpGroup::getId(){
    return id;
}

QString FtpGroup::getName(){
    return name;
}

void FtpGroup::setName(QString name){
    this->name=name;
}

QString FtpGroup::getPath(){
    return path;
}

void FtpGroup::setPath(QString path){
    this->path=path;
}

QString FtpGroup::getFile(){
    return file;
}

void FtpGroup::setFile(QString file){
    this->file=file;
}

QString FtpGroup::getDirectory(){
    return directory;
}

void FtpGroup::setDirectory(QString directory){
    this->directory=directory;
}
