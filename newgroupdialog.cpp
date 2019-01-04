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
{   //进行提示信息的初始化
    QPalette pe;
     pe.setColor(QPalette::WindowText,Qt::red);
      ui->inform->setPalette(pe);
       ui->inform2->setPalette(pe);
       ui->inform->setText("");
       ui->inform2->setText("");
        groupname=ui->groupname->text();
         path=ui->path->text();
          if(!groupname.isEmpty()&&!path.isEmpty()){
              if(sqlConnection->insertGroup(FtpGroup(groupname,path,"",""))){
                  qDebug()<<"添加用户组成功";
                  //发送刷新信号
                  emit refresh();
                  cancel();
              }
              else{
                  ui->inform->setText("该用户组已存在！");
              }
          }
          else {
              if(groupname.isEmpty()){
                  ui->inform->setText("请填写用户名！");
              }


              if(path.isEmpty()){

                  ui->inform2->setText("请选择路径！");
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
