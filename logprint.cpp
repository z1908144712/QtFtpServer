#include "logprint.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

/*
 * LogPrint打印日志
*/
LogPrint::LogPrint(QTextEdit *textEdit){
    this->textEdit=textEdit;
}

LogPrint::LogPrint(QTextEdit *textEdit,const QString text)
{
    this->textEdit=textEdit;
    this->text=text;
}

void LogPrint::setText(const QString text){
    this->text=text;
}

/*
 * 打印到界面或文件
*/
void LogPrint::print(){

    //打印到界面
    QDateTime current_data_time=QDateTime::currentDateTime();
    QString current_time=current_data_time.toString("hh:mm:ss.zzz");
    text="["+current_time+"] "+text;
    textEdit->append(text);

    //写入到文件
    QDir dir(".");
    if(!dir.exists("log")){
        dir.mkdir("log");
    }
    /*日志名字同当前时间*/
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyy-MM-dd");
    QString fileName = ".\\log\\" + timestr + ".log";//指定文件夹路径
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        qDebug("File open failed!");
    }else{
        /*写日志*/
       QTextStream text_stream(&file);
       text_stream << text << "\r\n";
       file.flush();
       file.close();
    }
}
