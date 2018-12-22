#ifndef FTPABOUT_H
#define FTPABOUT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class FtpAbout;
}

class FtpAbout : public QDialog
{
    Q_OBJECT

public:
    explicit FtpAbout(QWidget *parent = 0);
    ~FtpAbout();

private:
    Ui::FtpAbout *ui;
};

#endif // FTPABOUT_H
