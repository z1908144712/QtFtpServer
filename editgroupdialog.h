#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include <ftpsqlconnection.h>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupDialog(QWidget *parent,FtpSqlConnection *sqlConnection,FtpGroup ftpgroup);
    ~EditGroupDialog();

private:
    Ui::EditGroupDialog *ui;
    FtpSqlConnection *sqlConnection;
    QStandardItemModel *user_standardItemModel;
    FtpGroup ftpgroup;
    FtpUser  ftpUser;
    void showUserListInGroup();
    void refresh_user();
signals:
    void  refresh();
private slots:
    void confirm();
    void cancel();
    void findfile();
    void deleteuser();
    void user_list_item_click(const QModelIndex&);

};

#endif // EDITGROUPDIALOG_H
