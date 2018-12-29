#include "logprint.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

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

    /*日志名字同当前时间*/
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyy-MM-dd");
    QString fileName = "F:\\Computer\\AC\\log\\" + timestr + ".log";//指定文件夹路径
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("File open failed!");
    }

    QDateTime current_data_time=QDateTime::currentDateTime();
    QString current_time=current_data_time.toString("hh:mm:ss.zzz");
    text="["+current_time+"] "+text;
    textEdit->append(text);

     /*写日志*/
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << text << "\r\n";

    file.flush();
    file.close();
}
