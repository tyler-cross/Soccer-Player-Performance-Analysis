#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T10:16:35
#
#-------------------------------------------------

QT       += core gui
QMAKE_MAC_SDK = macosx10.12

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = soccerfield1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresources.qrc
