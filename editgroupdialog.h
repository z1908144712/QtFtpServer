#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include <ftpsqlconnection.h>

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
    FtpGroup ftpgroup;
signals:
    void  refresh();
private slots:
    void confirm();
    void cancel();
    void findfile();
};

#endif // EDITGROUPDIALOG_H
