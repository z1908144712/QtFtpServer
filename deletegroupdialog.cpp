#include "deletegroupdialog.h"
#include "ui_deletegroupdialog.h"
#include<QDebug>
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
     qDebug()<<groupname;
    int id=sqlConnection->queryGroupIdByName(groupname);
      qDebug()<<id;
    sqlConnection->deleteGroupById(id);

    emit refresh();
    cancel();
}

void DeleteGroupDialog::cancel(){
    this->close();
}
