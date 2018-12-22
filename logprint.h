#ifndef LOGPRINT_H
#define LOGPRINT_H

#include <QTextEdit>

class LogPrint
{
public:
    LogPrint(QTextEdit *textEdit);
    LogPrint(QTextEdit *textEdit,const QString text);
    void setText(const QString text);
    void print();
private:
    QTextEdit *textEdit;
    QString text;
};

#endif // LOGPRINT_H
