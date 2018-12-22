#include "ftpabout.h"
#include "ui_ftpabout.h"

/*
 * 显示作者信息
*/

FtpAbout::FtpAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpAbout)
{
    ui->setupUi(this);
    connect(ui->confirm,&QPushButton::clicked,[=](){
        this->close();
    });
}

FtpAbout::~FtpAbout()
{
    delete ui;
}
