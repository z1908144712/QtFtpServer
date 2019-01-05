#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"
#include<QDebug>
#include<QFileDialog>
#include<ftpgroup.h>
#include <QMessageBox>

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
{   //进行提示信息的初始化
    groupname=ui->groupname->text().trimmed();
    path=ui->path->text().trimmed();
    if(!groupname.isEmpty()&&!path.isEmpty()){
        if(sqlConnection->insertGroup(FtpGroup(groupname,path,"",""))){
            qDebug()<<"添加用户组成功";
            //发送刷新信号
            emit refresh();
            cancel();
        }
        else{
            QMessageBox::warning(this,"错误","该用户组已存在！");
        }
    }
    else {
        if(groupname.isEmpty()||path.isEmpty()){
            QMessageBox::warning(this,"错误","信息未完善！");
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
