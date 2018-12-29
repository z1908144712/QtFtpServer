#ifndef SETUSERGROUPWINDOW_H
#define SETUSERGROUPWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QPoint>
#include "newuserdialog.h"
#include "newgroupdialog.h"
#include "edituserdialog.h"
#include "editgroupdialog.h"
#include "deleteuserdialog.h"
#include "deletegroupdialog.h"
#include "ftpsqlconnection.h"
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class SetUserGroupWindow;
}

class SetUserGroupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetUserGroupWindow(QWidget *parent,FtpSqlConnection *sqlConnection);
    ~SetUserGroupWindow();


private:
    void init_data();
    void init_connect();

    Ui::SetUserGroupWindow *ui;
    NewUserDialog *newUserDialog;
    NewGroupDialog *newGroupDialog;
    DeleteUserDialog *deleteUserDialog;
    DeleteGroupDialog *deleteGroupDialog;
    EditGroupDialog *editGroupDialog;
    EditUserDialog *editUserDialog;
    FtpSqlConnection *sqlConnection;
    QStandardItemModel *group_standardItemModel;
    QStandardItemModel *user_standardItemModel;
    FtpUser ftpUser;
    FtpGroup ftpGroup;

    void showUserList();
    void showGroupList();
    void setFileAccess(QString file);
    void setDirectoryAcccess(QString directorty);
    void saveUserAccess();
    void saveGroupAccess();
    QString getFileAccess();
    QString getDirAccess();

    bool edit_or_save;
    //false时修改user,true时修改group
    bool save_user_or_group_access;

private slots:
    void newUser();
    void editUser();
    void deleteUser();
    void newGroup();
    void editGroup();
    void deleteGroup();
    void refresh_user();
    void refresh_group();
    void user_list_item_click(const QModelIndex&);
    void group_list_item_click(const QModelIndex&);
    void edit_or_save_access();

    //对权限控制界面的文件组件的设置
    void file_access_click();
    void file_no_access_click();
    //与上面一样
    void dir_access_click();
    void dir_no_access_click();
};

#endif // SETUSERGROUPWINDOW_H
