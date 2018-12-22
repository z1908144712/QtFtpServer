#include "mainwindow.h"
#include <QApplication>
#include "ftpcontrolconnection.h"

int FtpControlConnection::user_counter=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
