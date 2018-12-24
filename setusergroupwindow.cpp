#include "setusergroupwindow.h"
#include "ui_setusergroupwindow.h"
#include <QList>
#include <QMap>
#include <QDebug>

/*
 * 设置用户/用户组
*/
SetUserGroupWindow::SetUserGroupWindow(QWidget *parent,FtpSqlConnection *sqlConnection) :
    QDialog(parent),
    ui(new Ui::SetUserGroupWindow)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;

    init_data();
    init_connect();
}

SetUserGroupWindow::~SetUserGroupWindow()
{
    delete ui;
}

/*
 * 初始化数据
*/
void SetUserGroupWindow::init_data(){
    user_standardItemModel=new QStandardItemModel(this);
    group_standardItemModel=new QStandardItemModel(this);
    showUserList();
    showGroupList();
    edit_or_save=false;
}

/*
 * 初始化connect
*/
void SetUserGroupWindow::init_connect(){
    connect(ui->new_user,SIGNAL(clicked()),this,SLOT(newUser()));
    connect(ui->edit_user,SIGNAL(clicked()),this,SLOT(editUser()));
    connect(ui->delete_user,SIGNAL(clicked()),this,SLOT(deleteUser()));
    connect(ui->edit_access,SIGNAL(clicked()),this,SLOT(edit_or_save_access()));
    connect(ui->file_delete,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_upload,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_rename,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_download,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_no_access,SIGNAL(clicked()),this,SLOT(file_no_access_click()));
    connect(ui->dir_delete,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_new,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_rename,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_no_access,SIGNAL(clicked()),this,SLOT(dir_no_access_click()));
    connect(ui->user_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(user_list_item_click(const QModelIndex&)));
}

/*
 * 显示user_list
*/
void SetUserGroupWindow::showUserList(){
    QList<QMap<QString,QString>> list=sqlConnection->listUserNames();
    user_standardItemModel->clear();
    for(int i=0;i<list.size();i++){
        user_standardItemModel->appendRow(new QStandardItem(list.at(i)["name"]));
    }
    ui->user_list->setModel(user_standardItemModel);
}

/*
 * user_list item点击
*/
void SetUserGroupWindow::user_list_item_click(const QModelIndex &index){
    ui->edit_user->setEnabled(true);
    ui->delete_user->setEnabled(true);
    ui->groupBox_info->setEnabled(true);
    ui->edit_access->setEnabled(true);
    ui->file_access->setEnabled(false);
    ui->dir_access->setEnabled(false);
    ui->edit_access->setText("编辑权限");
    ftpUser=sqlConnection->queryUserByName(index.data().toString());
    ui->label_id->setText("用户ID");
    ui->label_name->setText("用户名");
    ui->label_group->setText("用户组");
    ui->label_path->setText("根目录");
    ui->id_value->setText(QString::number(ftpUser.getId()));
    ui->name_value->setText(ftpUser.getName());
    if(ftpUser.getFtpGroup()==0){
        ui->group_value->setText("未分组");
        ui->path_value->setText(ftpUser.getPath());
        setFileAccess(ftpUser.getFile());
        setDirectoryAcccess(ftpUser.getDirectory());
    }else{
        ftpGroup=sqlConnection->queryGroupById(ftpUser.getFtpGroup());
        ui->group_value->setText(ftpGroup.getName());
        ui->path_value->setText(ftpGroup.getPath());
        setFileAccess(ftpGroup.getFile());
        setDirectoryAcccess(ftpGroup.getDirectory());
    }

}

/*
 * file_access点击
*/
void SetUserGroupWindow::file_access_click(){
    ui->file_no_access->setCheckState(Qt::Unchecked);
}

/*
 * file_access点击
*/
void SetUserGroupWindow::file_no_access_click(){
    if(ui->file_no_access->isChecked()){
        ui->file_delete->setCheckState(Qt::Unchecked);
        ui->file_upload->setCheckState(Qt::Unchecked);
        ui->file_rename->setCheckState(Qt::Unchecked);
        ui->file_download->setCheckState(Qt::Unchecked);
    }
}

/*
 * dir_access点击
*/
void SetUserGroupWindow::dir_access_click(){
    ui->dir_no_access->setCheckState(Qt::Unchecked);
}

/*
 * dir_no_access点击
*/
void SetUserGroupWindow::dir_no_access_click(){
    if(ui->dir_no_access->isChecked()){
        ui->dir_delete->setCheckState(Qt::Unchecked);
        ui->dir_new->setCheckState(Qt::Unchecked);
        ui->dir_rename->setCheckState(Qt::Unchecked);
    }
}

/*
 * 显示文件权限
*/
void SetUserGroupWindow::setFileAccess(QString file){
    ui->file_delete->setCheckState(Qt::Unchecked);
    ui->file_upload->setCheckState(Qt::Unchecked);
    ui->file_rename->setCheckState(Qt::Unchecked);
    ui->file_download->setCheckState(Qt::Unchecked);
    ui->file_no_access->setCheckState(Qt::Unchecked);
    if(file.length()<4||file=="0000"){
        ui->file_no_access->setChecked(true);
        return;
    }
    if(file.at(0)=='1'){
        ui->file_delete->setChecked(true);
    }
    if(file.at(1)=='1'){
        ui->file_upload->setChecked(true);
    }
    if(file.at(2)=='1'){
        ui->file_rename->setChecked(true);
    }
    if(file.at(3)=='1'){
        ui->file_download->setChecked(true);
    }
}

/*
 * 显示目录权限
*/
void SetUserGroupWindow::setDirectoryAcccess(QString directorty){
    ui->dir_delete->setCheckState(Qt::Unchecked);
    ui->dir_new->setCheckState(Qt::Unchecked);
    ui->dir_rename->setCheckState(Qt::Unchecked);
    ui->dir_no_access->setCheckState(Qt::Unchecked);
    if(directorty.length()<4||directorty=="000"){
        ui->dir_no_access->setChecked(true);
        return;
    }
    if(directorty.at(0)=='1'){
        ui->dir_delete->setChecked(true);
    }
    if(directorty.at(1)=='1'){
        ui->dir_new->setChecked(true);
    }
    if(directorty.at(2)=='1'){
        ui->dir_rename->setChecked(true);
    }
}

/*
 * 显示group_list
*/
void SetUserGroupWindow::showGroupList(){
    QList<QMap<QString,QString>> list=sqlConnection->listGroupNames();
    group_standardItemModel->clear();
    for(int i=0;i<list.size();i++){
        group_standardItemModel->appendRow(new QStandardItem(list.at(i)["name"]));
    }
    ui->group_list->setModel(group_standardItemModel);
}

/*
 * group_list item 点击
*/
void SetUserGroupWindow::group_list_item_click(const QModelIndex &index){

}

/*
 * user操作后刷新必要控件
*/
void SetUserGroupWindow::refresh_user(){
    showUserList();
    ui->edit_user->setEnabled(false);
    ui->delete_user->setEnabled(false);
    ui->groupBox_info->setEnabled(false);
    ui->id_value->setText("");
    ui->name_value->setText("");
    ui->group_value->setText("");
    ui->path_value->setText("");
    ui->file_access->setEnabled(false);
    ui->dir_access->setEnabled(false);
    ui->file_delete->setCheckState(Qt::Unchecked);
    ui->file_upload->setCheckState(Qt::Unchecked);
    ui->file_rename->setCheckState(Qt::Unchecked);
    ui->file_download->setCheckState(Qt::Unchecked);
    ui->file_no_access->setCheckState(Qt::Unchecked);
    ui->dir_delete->setCheckState(Qt::Unchecked);
    ui->dir_new->setCheckState(Qt::Unchecked);
    ui->dir_rename->setCheckState(Qt::Unchecked);
    ui->dir_no_access->setCheckState(Qt::Unchecked);
    ui->edit_access->setEnabled(false);
    ui->edit_access->setText("编辑权限");
    edit_or_save=false;
}

/*
 * group操作后刷新必要控件
*/
void SetUserGroupWindow::refresh_group(){
    showGroupList();
}

/*
 * 保存编辑权限
*/
void SetUserGroupWindow::edit_or_save_access(){
    if(!edit_or_save){
        edit_or_save=true;
        ui->file_access->setEnabled(true);
        ui->dir_access->setEnabled(true);
        ui->edit_access->setText("保存权限");
    }else{
        edit_or_save=false;
        ui->file_access->setEnabled(false);
        ui->dir_access->setEnabled(false);
        ui->edit_access->setText("编辑权限");
    }
}

/*
 * 弹出新建用户界面
*/
void SetUserGroupWindow::newUser(){
    newUserDialog=new NewUserDialog(this,sqlConnection);
    connect(newUserDialog,SIGNAL(refresh()),this,SLOT(refresh_user()));
    newUserDialog->exec();
}

/*
 * 弹出编辑用户界面
*/
void SetUserGroupWindow::editUser(){

}

/*
 * 弹出删除用户界面
*/
void SetUserGroupWindow::deleteUser(){
    deleteUserDialog=new DeleteUserDialog(this,sqlConnection,ftpUser.getId(),ftpUser.getName());
    connect(deleteUserDialog,SIGNAL(refresh()),this,SLOT(refresh_user()));
    deleteUserDialog->exec();
}

/*
 * 弹出新建用户组界面
*/
void SetUserGroupWindow::newGroup(){

}

/*
 * 弹出编辑用户组界面
*/
void SetUserGroupWindow::editGroup(){

}

/*
 * 弹出删除用户组界面
*/
void SetUserGroupWindow::deleteGroup(){

}
