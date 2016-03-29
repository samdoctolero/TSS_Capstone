#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T18:10:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI1
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
        Ping.cpp\
        IR.cpp\
        TempHumid.cpp\
        RelayBoard.cpp\
        ConfigManager.cpp\
        BusInfo.cpp\
        Solar.cpp\


HEADERS  += widget.h \
        Ping.h\
        IR.h\
        TempHumid.h\
        RelayBoard.h\
        ConfigManager.h\
        BusInfo.h\
        Solar.h\

FORMS    += widget.ui

OTHER_FILES += configuration.txt\

LIBS += -lwiringPi\
        -lpthread\
        -lmodbus\

