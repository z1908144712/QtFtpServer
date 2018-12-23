#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"
#include <QMessageBox>

DeleteUserDialog::DeleteUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection,int id,QString username) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    this->id=id;
    this->username=username;
    ui->info->setText("确定删除用户："+username+" ?");
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

void DeleteUserDialog::confirm(){
    if(sqlConnection->hasUserByName(username)){
        if(!sqlConnection->deleteUserById(id)){
            QMessageBox::warning(this,"错误","删除失败！");
        }else{
            emit refresh();
        }
    }else{
        QMessageBox::warning(this,"错误","删除失败！");
    }
    this->close();
}

void DeleteUserDialog::cancel(){
    this->close();
}
