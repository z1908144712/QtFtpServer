#ifndef DELETEGROUPDIALOG_H
#define DELETEGROUPDIALOG_H

#include <QDialog>
#include <ftpsqlconnection.h>
#include<ftpgroup.h>
namespace Ui {
class DeleteGroupDialog;
}

class DeleteGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteGroupDialog(QWidget *parent, FtpSqlConnection *sqlConnection,int id,QString groupname);
    ~DeleteGroupDialog();

private:
    Ui::DeleteGroupDialog *ui;
    FtpSqlConnection *sqlConnection;
    int id;
    QString groupname;
signals:
   void  refresh();
private slots:
    void confirm();
    void cancel();
};

#endif // DELETEGROUPDIALOG_H
