#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H

#include <QDialog>
#include<ftpsqlconnection.h>
namespace Ui {
class NewGroupDialog;
}

class NewGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGroupDialog(QWidget *parent,FtpSqlConnection *sqlConnection);
    ~NewGroupDialog();
signals:
    void refresh();
private:
    Ui::NewGroupDialog *ui;
    FtpSqlConnection *sqlConnection;
    QString groupname;
     QString path;
public slots:
    void confirm();
    void cancel();
    void findfile();
};

#endif // NEWGROUPDIALOG_H
