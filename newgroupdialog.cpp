#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"
#include<QDebug>
#include<QFileDialog>
#include<ftpgroup.h>
NewGroupDialog::NewGroupDialog(QWidget *parent,FtpSqlConnection *sqlConnection) :
    QDialog(parent),
    ui(new Ui::NewGroupDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    connect(ui->confirm,&QPushButton::clicked,this,&NewGroupDialog::confirm);
    connect(ui->findpath,&QPushButton::clicked,this,&NewGroupDialog::findfile);
    connect(ui->cancel,&QPushButton::clicked,this,&NewGroupDialog::cancel);
}

NewGroupDialog::~NewGroupDialog()
{
    delete ui;
}


void NewGroupDialog::confirm()
{
    groupname=ui->groupname->text();
    path=ui->path->text();
    if(!groupname.isEmpty()&&!path.isEmpty()){
        if(sqlConnection->insertGroup(FtpGroup(groupname,path,"",""))){
            qDebug()<<"添加用户组成功";
            //发送刷新信号
            emit refresh();
            cancel();
        }
    }

}
void NewGroupDialog::cancel()
{
    this->close();
}
void NewGroupDialog::findfile(){
    ui->path->setText(QFileDialog::getExistingDirectory(this,"选取","."));
}
