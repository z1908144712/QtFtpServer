#include "edituserdialog.h"
#include "ui_edituserdialog.h"
#include "ftpcrypto.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

EditUserDialog::EditUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection,FtpUser ftpUser) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    this->ftpUser=ftpUser;
    ui->username->setText(ftpUser.getName());
    ui->password1->setText(ftpUser.getPassword());
    ui->password2->setText(ftpUser.getPassword());
    QList<QMap<QString,QString>> list=this->sqlConnection->listGroupNames();
    if(ftpUser.getFtpGroup()==0){
        ui->groups->insertItem(0,"未分组");
        for(int i=0;i<list.size();i++){
            ui->groups->insertItem(i+1,list.at(i)["name"]);
        }
        ftpgroup="未分组";
        ui->groups->setCurrentText("未分组");
        if(ftpUser.getPath().isEmpty()){
            ui->path->setText("未指定");
        }else{
            ui->path->setText(ftpUser.getPath());
        }
    }else{
        for(int i=0;i<list.size();i++){
            ui->groups->insertItem(i,list.at(i)["name"]);
        }
        ftpgroup=sqlConnection->queryGroupNameById(ftpUser.getFtpGroup());
        ui->groups->setCurrentText(ftpgroup);
        ui->path->setText(sqlConnection->queryGroupPathByName(ftpgroup));
        ui->findfile->setEnabled(false);
    }
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui->findfile,SIGNAL(clicked()),this,SLOT(findfile()));
    connect(ui->groups,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(combobox_item_changed(const QString&)));
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::findfile(){
    QString filepath=QFileDialog::getExistingDirectory(this,"选取",ftpUser.getPath());
    if(!filepath.isEmpty()){
        ui->path->setText(filepath);
    }
}

//点击进行修改
void EditUserDialog::confirm(){
    QString username=ui->username->text().trimmed();
    QString password1=ui->password1->text().trimmed();
    QString password2=ui->password2->text().trimmed();
    QString group=ui->groups->currentText();
    QString path=ui->path->text().trimmed();
    if(!username.isEmpty()&&!password1.isEmpty()&&!password2.isEmpty()&&!group.isEmpty()&&!path.isEmpty()){
        if(username!=ftpUser.getName()&&sqlConnection->hasUserByName(username)){
            QMessageBox::warning(this,"错误","该用户已存在！");
            ui->username->setText(ftpUser.getName());
            return;
        }
        if(password1!=password2){
            QMessageBox::warning(this,"错误","两次输入的密码不一致！");
            return;
        }else{
            password1=FtpCrypto::cryptopassword(password1);
        }
        if(username!=ftpUser.getName()||password1!=ftpUser.getPassword()||group!=ftpgroup||path!=ftpUser.getPath()){
            if(username!=ftpUser.getName()){
                ftpUser.setName(username);
            }
            if(password1!=ftpUser.getPassword()){
                ftpUser.setPassword(password1);
            }
            if(group!=ftpgroup){
                ftpUser.setFtpGroup(sqlConnection->queryGroupIdByName(group));
            }
            if(path!="未指定"&&path!=ftpUser.getPath()){
                ftpUser.setPath(path);
            }
            if(!sqlConnection->updateUserBasic(ftpUser)){
                QMessageBox::warning(this,"错误","修改失败！");
            }else{
                this->close();
                emit refresh();
            }
        }
    }else{
        QMessageBox::warning(this,"错误","信息未完善！");
        if(username.isEmpty()){
            ui->username->setText(ftpUser.getName());
        }
        if(password1.isEmpty()){
            ui->password1->setText(ftpUser.getPassword());
        }
        if(password2.isEmpty()){
            ui->password2->setText(ftpUser.getPassword());
        }
    }
}

void EditUserDialog::cancel(){
    this->close();
    emit refresh();
}

void EditUserDialog::combobox_item_changed(const QString &group){
    if(group=="未分组"){
        if(ftpUser.getPath().isEmpty()){
            ui->path->setText("未指定");
        }else{
            ui->path->setText(ftpUser.getPath());
        }
    }else{
        ui->path->setText(sqlConnection->queryGroupPathByName(group));
    }
}
