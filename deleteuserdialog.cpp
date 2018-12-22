#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"

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

}

void DeleteUserDialog::cancel(){
    this->close();
}
