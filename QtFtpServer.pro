#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T21:25:55
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFtpServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    ftpcommand.cpp \
    sslserver.cpp \
    dataconnection.cpp \
    ftplistcommand.cpp \
    ftpretrcommand.cpp \
    ftpstorcommand.cpp \
    ftpcontrolconnection.cpp \
    logprint.cpp \
    ftpserver.cpp \
    ftpsqlconnection.cpp \
    ftpgroup.cpp \
    ftpuser.cpp \
    setusergroupwindow.cpp \
    newuserdialog.cpp \
    ftpabout.cpp \
    ftpcrypto.cpp \
    deleteuserdialog.cpp \
    newgroupdialog.cpp \
    deletegroupdialog.cpp \
    edituserdialog.cpp \
    editgroupdialog.cpp

HEADERS  += mainwindow.h \
    ftpcommand.h \
    sslserver.h \
    dataconnection.h \
    ftplistcommand.h \
    ftpretrcommand.h \
    ftpstorcommand.h \
    ftpcontrolconnection.h \
    logprint.h \
    ftpserver.h \
    ftpsqlconnection.h \
    ftpgroup.h \
    ftpuser.h \
    setusergroupwindow.h \
    newuserdialog.h \
    ftpabout.h \
    ftpcrypto.h \
    deleteuserdialog.h \
    newgroupdialog.h \
    deletegroupdialog.h \
    edituserdialog.h \
    editgroupdialog.h

FORMS    += mainwindow.ui \
    setusergroupwindow.ui \
    newuserdialog.ui \
    ftpabout.ui \
    deleteuserdialog.ui \
    newgroupdialog.ui \
    deletegroupdialog.ui \
    edituserdialog.ui \
    editgroupdialog.ui

RESOURCES += \
    res.qrc

CONFIG += c++11
