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
    QString ftpgroup;
signals:
    void  refresh();
private slots:
    void findfile();
    void confirm();
    void cancel();
    void combobox_item_changed(const QString&);
};

#endif // EDITUSERDIALOG_H
