#include "deletegroupdialog.h"
#include "ui_deletegroupdialog.h"
#include<QDebug>
#include<QMessageBox>
DeleteGroupDialog::DeleteGroupDialog(QWidget *parent,FtpSqlConnection *sqlConnection,int id,QString groupname) :
    QDialog(parent),
    ui(new Ui::DeleteGroupDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    this->id=id;
    this->groupname=groupname;
    ui->info->setText("确定删除用户组："+groupname+" ?");
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

DeleteGroupDialog::~DeleteGroupDialog()
{
    delete ui;
}
void DeleteGroupDialog::confirm(){
  //点击确定删除
     //qDebug()<<groupname;
    int id=sqlConnection->queryGroupIdByName(groupname);
      //qDebug()<<id;
    sqlConnection->deleteGroupById(id);
    //删除用户组的话，对应组里的用户的分组属性也会被修改
    //先找到当前组的用户列表
    QList<QMap<QString,QString>> list=sqlConnection->listUserNamesInGroup(id);
    //然后一一更新他们的属性
    for(int i=0;i<list.size();i++){
     FtpUser ftpUser=sqlConnection->queryUserByName(list.at(i)["name"]);
       ftpUser.setFtpGroup(0);
       if(!sqlConnection->updateUserBasic(ftpUser)){//更新用户信息
           QMessageBox::warning(this,"错误","修改失败！");
       }
    }
    emit refresh();
    cancel();
}

void DeleteGroupDialog::cancel(){
    this->close();
}
