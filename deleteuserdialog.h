#ifndef DELETEUSERDIALOG_H
#define DELETEUSERDIALOG_H

#include <QDialog>
#include <ftpsqlconnection.h>

namespace Ui {
class DeleteUserDialog;
}

class DeleteUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection,int id,QString username);
    ~DeleteUserDialog();

private:
    Ui::DeleteUserDialog *ui;
    FtpSqlConnection *sqlConnection;
    int id;
    QString username;
private slots:
    void confirm();
    void cancel();
};

#endif // DELETEUSERDIALOG_H
