#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T16:58:05
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleTCPServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp \
    traciwrapper.cpp

HEADERS  += mainwindow.h \
    tcpserver.h \
    TraCIConstants.h \
    traciwrapper.h \
    VTIConstants.h

FORMS    += \
    mainwindow.ui
