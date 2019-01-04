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
    user_standardItemModel=new QStandardItemModel(this);
    showUserListInGroup();//显示用户列表
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui->deleteuser,SIGNAL(clicked()),this,SLOT(deleteuser()));
    connect(ui->findpath,&QPushButton::clicked,this,&EditGroupDialog::findfile);
    //点击用户列表的信号与槽
    connect(ui->user_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(user_list_item_click(const QModelIndex&)));

}


EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}

void EditGroupDialog::confirm(){
  //将修改后的值保存至当前对象
    ftpgroup.setName(ui->groupname->text());
    ftpgroup.setPath(ui->path->text());
    if(sqlConnection->hasGroupByName(ftpgroup.getName())){
        QPalette pe;
         pe.setColor(QPalette::WindowText,Qt::red);
        ui->inform->setPalette(pe);
        ui->inform->setText("用户组名已存在！");
    }
    else{
        if(sqlConnection->updateGroupBasic(ftpgroup)){
            emit refresh();
            cancel();

        }

    }
}

/*
 * 显示用户列表（在当前用户组中的）
*/
void EditGroupDialog::showUserListInGroup(){
    QList<QMap<QString,QString>> list=sqlConnection->listUserNamesInGroup(ftpgroup.getId());
    qDebug()<<list.size();
    for(int i=0;i<list.size();i++){
     qDebug()<<list.at(i)["id"]<<list.at(i)["name"];
    }

    user_standardItemModel->clear();
    for(int i=0;i<list.size();i++){
      user_standardItemModel->appendRow(new QStandardItem(list.at(i)["name"]));
    }
    ui->user_list->setModel(user_standardItemModel);
}

/*
 * 点击用户列表触发的槽函数
*/
void EditGroupDialog::user_list_item_click(const QModelIndex &index){
//显示删除用户可见
    ui->deleteuser->setEnabled(true);
    //创建选中的用户对象
    ftpUser=sqlConnection->queryUserByName(index.data().toString());
}
/*
 * 删除用户组中的用户
*/
void EditGroupDialog::deleteuser(){
    //这样子的话，用户的选定的用户组就不存在了，修改这个对象对应的属性
    ftpUser.setFtpGroup(0);//用户选的组就恢复了默认
    if(!sqlConnection->updateUserBasic(ftpUser)){//更新数据库
        QMessageBox::warning(this,"错误","修改失败！");
    }else{  //刷新用户界面
        ui->deleteuser->setEnabled(false);
        showUserListInGroup();
        emit refresh();
    }
}
void EditGroupDialog::refresh_user(){
   showUserListInGroup();
}
void EditGroupDialog::cancel(){
    this->close();
}
void EditGroupDialog::findfile(){
    ui->path->setText(QFileDialog::getExistingDirectory(this,"选取","."));
}
