#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "ftpsqlconnection.h"

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection);
    ~NewUserDialog();
signals:
    void refresh();

private:
    Ui::NewUserDialog *ui;
    FtpSqlConnection *sqlConnection;
    QFileDialog fileDialog;
    QString username;
    QString password1;
    QString password2;
    QString path;
    int group;
private slots:
    void confirm();
    void cancel();
    void findfile();
};

#endif // NEWUSERDIALOG_H
