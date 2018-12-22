#include "logprint.h"

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
    QDateTime current_data_time=QDateTime::currentDateTime();
    QString current_time=current_data_time.toString("hh:mm:ss.zzz");
    text="["+current_time+"] "+text;
    textEdit->append(text);
}
