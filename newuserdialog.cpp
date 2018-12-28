#include "newuserdialog.h"
#include "ui_newuserdialog.h"
#include <QList>
#include <QMap>
#include <QDebug>
#include "ftpuser.h"
#include "ftpcrypto.h"

/*
 * 新建用户Dialog
*/
NewUserDialog::NewUserDialog(QWidget *parent,FtpSqlConnection *sqlConnection) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
    this->sqlConnection=sqlConnection;
    QList<QMap<QString,QString>> list=this->sqlConnection->listGroupNames();//这是用户组列表（id,名字）
    ui->groups->insertItem(0,"默认");
    for(int i=0;i<list.size();i++){
        ui->groups->insertItem(i+1,list.at(i)["name"]);//在控件中显示用户组列表
    }
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirm()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui->findfile,SIGNAL(clicked()),this,SLOT(findfile()));
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}

/*
 * 确定按钮点击，插入数据
 * @return void
*/
void NewUserDialog::confirm(){
    username=ui->username->text().trimmed();
    password1=ui->password1->text().trimmed();
    password2=ui->password2->text().trimmed();
    path=ui->path->text().trimmed();
    group=ui->groups->currentIndex();//获取到当前选中的用户组列表的下标
    //qDebug()<<group;
    if(!username.isEmpty()&&!password1.isEmpty()&&!password2.isEmpty()){
        if(password1==password2){
            QString crypto_password=FtpCrypto::cryptopassword(password1);
            if(group==0){//0表示选中的用户组是默认的
                if(!path.isEmpty()){
                    if(sqlConnection->insertUser(FtpUser(username,crypto_password,group,path,"0000","000"))){//直接把0传过去，表示选的用户组是默认的
                        emit refresh();
                        cancel();
                    }
                }
            }else{//表示选择了用户组
                group=sqlConnection->queryGroupIdByName(ui->groups->currentText());//获取到选中的列表的文本---就是用户组的名字  再根据选择组的名字找到组的id
                if(sqlConnection->insertUser(FtpUser(username,crypto_password,group,"","",""))){
                    emit refresh();
                    cancel();
                }
            }
        }
    }
}

/*
 * 取消按钮点击
 * @return void
*/
void NewUserDialog::cancel(){
    this->close();
}

/*
 * 选取path
 * @return void
*/
void NewUserDialog::findfile(){
    ui->path->setText(QFileDialog::getExistingDirectory(this,"选取","."));
}
