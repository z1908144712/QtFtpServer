#include "edituserdialog.h"
#include "ui_edituserdialog.h"

EditUserDialog::EditUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection,FtpUser ftpUser) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
    this->ftpUser=ftpUser;
    //因为是修改，界面应该显示原来的数据
  ui->username->setText(ftpUser.getName());
  ui->password1->setText(ftpUser.getPassword());
  ui->password2->setText(ftpUser.getPassword());
  ui->path->setText(ftpUser.getPath());
  //未完

}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}
void EditUserDialog::confirm(){
  //点击进行修改

}

void EditUserDialog::cancel(){
    this->close();
}
