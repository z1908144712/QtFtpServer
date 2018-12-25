#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <ftpsqlconnection.h>
namespace Ui {
class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection,FtpUser ftpUser);
    ~EditUserDialog();

private:
    Ui::EditUserDialog *ui;
    FtpSqlConnection *sqlConnection;
    FtpUser ftpUser;
    int id;
signals:
    void  refresh();
private slots:
    void confirm();
    void cancel();
};

#endif // EDITUSERDIALOG_H
