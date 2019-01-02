#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"
#include<QDebug>
#include<qfiledialog.h>
EditGroupDialog::EditGroupDialog(QWidget *parent,FtpSqlConnection *sqlConnection,FtpGroup ftpgroup) :
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    this->ftpgroup=ftpgroup;
    //因为是修改，界面应该显示原来的数据
    ui->groupname->setText(ftpgroup.getName());
    ui->path->setText(ftpgroup.getPath());
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui->findpath,&QPushButton::clicked,this,&EditGroupDialog::findfile);
}

EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}
void EditGroupDialog::confirm(){
  //将修改后的值保存至当前对象
    ftpgroup.setName(ui->groupname->text());
    ftpgroup.setPath(ui->path->text());
    qDebug()<<ftpgroup.getName();
    qDebug()<<ftpgroup.getPath();
    if(sqlConnection->updateGroupBasic(ftpgroup)){
        emit refresh();
        cancel();

    }


}

void EditGroupDialog::cancel(){
    this->close();
}
void EditGroupDialog::findfile(){
    ui->path->setText(QFileDialog::getExistingDirectory(this,"选取","."));
}
