#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T21:32:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolitaireCipher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core/solitairecrypto.cpp

HEADERS  += mainwindow.h \
    core/solitairecrypto.h

FORMS    += mainwindow.ui
