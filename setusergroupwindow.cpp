#include "setusergroupwindow.h"
#include "ui_setusergroupwindow.h"
#include <QList>
#include <QMap>
#include <QDebug>
#include <QMessageBox>

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
    connect(ui->new_group,SIGNAL(clicked()),this,SLOT(newGroup()));
    connect(ui->edit_user,SIGNAL(clicked()),this,SLOT(editUser()));
    connect(ui->edit_group,SIGNAL(clicked()),this,SLOT(editGroup()));
    connect(ui->delete_user,SIGNAL(clicked()),this,SLOT(deleteUser()));
    connect(ui->delete_group,SIGNAL(clicked()),this,SLOT(deleteGroup()));
    connect(ui->edit_access,SIGNAL(clicked()),this,SLOT(edit_or_save_access()));

    //这两组是设置控件的隐显，针对于文件的，如果选了其他的就不能选择无权限；如果选择了无权限，则不能选其他的
    //这个功能分别在两个槽函数中实现 file_access_click() file_no_access_click()
    connect(ui->file_delete,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_upload,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_rename,SIGNAL(clicked()),this,SLOT(file_access_click()));
    connect(ui->file_download,SIGNAL(clicked()),this,SLOT(file_access_click()));
    //对应于    如果选择了无权限，则不能选其他的
    connect(ui->file_no_access,SIGNAL(clicked()),this,SLOT(file_no_access_click()));

    //同上  这是针对   目录的
    connect(ui->dir_delete,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_new,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_rename,SIGNAL(clicked()),this,SLOT(dir_access_click()));
    connect(ui->dir_no_access,SIGNAL(clicked()),this,SLOT(dir_no_access_click()));

    //点击用户列表的信号与槽
    connect(ui->user_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(user_list_item_click(const QModelIndex&)));
    //点击用户组列表的信号与槽
    connect(ui->group_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(group_list_item_click(const QModelIndex&)));
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

    //编辑用户和删除用户的按钮可见
    ui->edit_user->setEnabled(true);
    ui->delete_user->setEnabled(true);

    //不可编辑或删除用户组
    ui->edit_group->setEnabled(false);
    ui->delete_group->setEnabled(false);

    //可编辑user权限
    save_user_or_group_access=false;

    //使右边第一个菜单栏可见
    ui->groupBox_info->setEnabled(true);

    ui->edit_access->setEnabled(true);//编辑权限的按钮，点击按钮才可以权限配置
    ui->file_access->setEnabled(false);
    ui->dir_access->setEnabled(false);
    ui->edit_access->setText("编辑权限");
    ftpUser=sqlConnection->queryUserByName(index.data().toString());//通过当前index来获取用户名并创建用户
    //设置右边的第一个菜单栏的显示
    ui->label_id->setText("用户ID");
    ui->label_name->setText("用户名");
    ui->label_group->setText("用户组");
    ui->label_path->setText("根目录");

    //为其赋值
    ui->id_value->setText(QString::number(ftpUser.getId()));
    ui->name_value->setText(ftpUser.getName());
    if(ftpUser.getFtpGroup()==0){//未分组时用户的权限为主
        ui->group_value->setText("未分组");
        if(ftpUser.getPath().isEmpty()){
            ui->path_value->setText("未指定");
            ui->edit_access->setEnabled(false);
        }else{
            ui->path_value->setText(ftpUser.getPath());
        }
        setFileAccess(ftpUser.getFile());
        setDirectoryAcccess(ftpUser.getDirectory());
    }else{//当分组以后，用户组的设置高于用户，显示的就是用户组的对路径，权限的设置
        ftpGroup=sqlConnection->queryGroupById(ftpUser.getFtpGroup());
        ui->group_value->setText(ftpGroup.getName());
        ui->path_value->setText(ftpGroup.getPath());
        setFileAccess(ftpGroup.getFile());
        setDirectoryAcccess(ftpGroup.getDirectory());
        ui->edit_access->setEnabled(false);
    }

}

/*
 * file_access点击
*/
void SetUserGroupWindow::file_access_click(){//选中了其他选择，则无权限就不能是被选中状态的
    ui->file_no_access->setCheckState(Qt::Unchecked);
}

/*
 * file_access点击
*/
void SetUserGroupWindow::file_no_access_click(){
    if(ui->file_no_access->isChecked()){//就是设置如果选中了无权限 file_no_access,那么其他选取就都不能选了
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
    if(directorty.length()<3||directorty=="000"){
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

    //编辑用户组和删除用户组的按钮可见
    ui->edit_group->setEnabled(true);
    ui->delete_group->setEnabled(true);

    //编辑用户和删除用户的按钮不可见
    ui->edit_user->setEnabled(false);
    ui->delete_user->setEnabled(false);

    //可编辑group权限
    save_user_or_group_access=true;//表示现在编辑的是用户组的权限

    //使右边第一个菜单栏可见
    ui->groupBox_info->setEnabled(true);

    ui->edit_access->setEnabled(true);//编辑权限的按钮，点击按钮才可以权限配置
    ui->file_access->setEnabled(false);
    ui->dir_access->setEnabled(false);
    ui->edit_access->setText("编辑权限");
    //创建一个当前选中的用户组对象
    ftpGroup=sqlConnection->queryGroupByName(index.data().toString());
    //设置右边的第一个菜单栏的显示
    ui->label_id->setText("用户组ID");
    ui->label_name->setText("用户组名");
    ui->label_group->setText("组员个数");
    ui->label_path->setText("根目录");

    //为其赋值
    ui->id_value->setText(QString::number(ftpGroup.getId()));
    ui->name_value->setText(ftpGroup.getName());
    int num=sqlConnection->queryUserNumInGroup(ftpGroup.getId());
    ui->group_value->setText(QString::number(num));
    ui->path_value->setText(ftpGroup.getPath());

    //还需要显示出当前用户组的权限设置
    setFileAccess(ftpGroup.getFile());
    setDirectoryAcccess(ftpGroup.getDirectory());
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
 * 保存编辑权限
*/
void SetUserGroupWindow::edit_or_save_access(){
    if(!edit_or_save){
        //修改权限
        edit_or_save=true;
        ui->file_access->setEnabled(true);
        ui->dir_access->setEnabled(true);
        ui->edit_access->setText("保存权限");
    }else{
        //保存权限
        if(!save_user_or_group_access){//设置的是用户的权限
            saveUserAccess();
        }else{//设置的是用户组的权限
            saveGroupAccess();
        }
        edit_or_save=false;
        ui->file_access->setEnabled(false);
        ui->dir_access->setEnabled(false);
        ui->edit_access->setText("编辑权限");
    }
}

/*
 * 保存用户权限
*/
void SetUserGroupWindow::saveUserAccess(){
    QString user_file_access=getFileAccess();
    QString user_dir_access=getDirAccess();
    if(user_file_access!=ftpUser.getFile()&&user_dir_access!=ftpUser.getDirectory()){
        if(!sqlConnection->updateUserFileAndDirAccess(ftpUser.getId(),user_file_access,user_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");
        }
    }else if(user_file_access!=ftpUser.getFile()){
        if(!sqlConnection->updateUserFileAccess(ftpUser.getId(),user_file_access)){
            QMessageBox::warning(this,"错误","修改失败！");
        }
    }else{
        if(!sqlConnection->updateUserDirAccess(ftpUser.getId(),user_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");
        }
    }
}

/*
 * 保存的是用户权限
*/
void SetUserGroupWindow::saveUserAccess(){
    QString user_file_access=getFileAccess();
    QString user_dir_access=getDirAccess();
    if(user_file_access!=ftpUser.getFile()&&user_dir_access!=ftpUser.getDirectory()){
        if(!sqlConnection->updateUserFileAndDirAccess(ftpUser.getId(),user_file_access,user_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");//目录和文件权限都修改
        }
    }else if(user_file_access!=ftpUser.getFile()){
        if(!sqlConnection->updateUserFileAccess(ftpUser.getId(),user_file_access)){
            QMessageBox::warning(this,"错误","修改失败！");//修改文件权限
        }
    }else{
        if(!sqlConnection->updateUserDirAccess(ftpUser.getId(),user_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");//修改目录权限
        }
    }
}

/*
 * 保存的是用户组权限
*/
void SetUserGroupWindow::saveGroupAccess(){
    QString group_file_access=getFileAccess();//获取到当前设置的权限
    QString group_dir_access=getDirAccess();
    // qDebug()<<"界面设置的是"<<group_file_access<<group_dir_access;
    if(group_file_access!=ftpGroup.getFile()&&group_dir_access!=ftpGroup.getDirectory()){//界面的与对象存的不一样，说明进行了修改，那就需要更新
       // qDebug()<<"对象中存储的是"<<ftpGroup.getFile()<<ftpGroup.getDirectory();
        if(!sqlConnection->updateGroupFileAndDirAccess(ftpGroup.getId(),group_file_access,group_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");//目录和文件权限都修改
        }
    }else if(group_file_access!=ftpUser.getFile()){
        if(!sqlConnection->updateGroupFileAccess(ftpGroup.getId(),group_file_access)){
            QMessageBox::warning(this,"错误","修改失败！");//修改文件权限
        }
    }else{
        if(!sqlConnection->updateGroupDirAccess(ftpGroup.getId(),group_dir_access)){
            QMessageBox::warning(this,"错误","修改失败！");//修改目录权限
        }
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
    editUserDialog=new EditUserDialog(this,sqlConnection,ftpUser);
    connect(editUserDialog,SIGNAL(refresh()),this,SLOT(refresh_user()));//接收到更新信号后就更新列表
    editUserDialog->exec();
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
     newGroupDialog=new NewGroupDialog(this,sqlConnection);
     connect(newGroupDialog,SIGNAL(refresh()),this,SLOT(refresh_group()));//接收到更新信号后就更新列表
     newGroupDialog->exec();
}

/*
 * 弹出编辑用户组界面
*/
void SetUserGroupWindow::editGroup(){
    editGroupDialog=new EditGroupDialog(this,sqlConnection,ftpGroup);
    connect(editGroupDialog,SIGNAL(refresh()),this,SLOT(refresh_group()));//接收到更新信号后就更新列表
    editGroupDialog->exec();
}

/*
 * 弹出删除用户组界面
*/
void SetUserGroupWindow::deleteGroup(){
    deleteGroupDialog=new DeleteGroupDialog(this,sqlConnection,ftpGroup.getId(),ftpGroup.getName());
    connect(deleteGroupDialog,SIGNAL(refresh()),this,SLOT(refresh_group()));//接收到更新信号后就更新列表
    deleteGroupDialog->exec();
}

/*
 * 获取当前文件权限
*/
QString SetUserGroupWindow::getFileAccess(){
    if(ui->file_no_access->isChecked()){
        return "0000";
    }else{
        QString file_access="";
        if(ui->file_delete->isChecked()){
            file_access+="1";
        }else{
            file_access+="0";
        }
        if(ui->file_upload->isChecked()){
            file_access+="1";
        }else{
            file_access+="0";
        }
        if(ui->file_rename->isChecked()){
            file_access+="1";
        }else{
            file_access+="0";
        }
        if(ui->file_download->isChecked()){
            file_access+="1";
        }else{
            file_access+="0";
        }
        return file_access;
    }
}

/*
 * 获取当前目录权限
*/
QString SetUserGroupWindow::getDirAccess(){
    if(ui->dir_no_access->isChecked()){
        return "000";
    }else{
        QString dir_access="";
        if(ui->dir_delete->isChecked()){
            dir_access+="1";
        }else{
            dir_access+="0";
        }
        if(ui->dir_new->isChecked()){
            dir_access+="1";
        }else{
            dir_access+="0";
        }
        if(ui->dir_rename->isChecked()){
            dir_access+="1";
        }else{
            dir_access+="0";
        }
        return dir_access;
    }
}
