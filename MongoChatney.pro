#-------------------------------------------------
#
# Project created by QtCreator 2017-10-06T01:41:26
#
#-------------------------------------------------

QT       += core network gui widgets sql

TARGET = MongoChatney
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    chatwindow.cpp \
    client.cpp \
    server.cpp \
    newconnectiondialog.cpp \
    connection.cpp \
    database.cpp

HEADERS += \
    mongochatneydefs.h \
    chatwindow.h \
    client.h \
    server.h \
    newconnectiondialog.h \
    connection.h \
    database.h

FORMS += \
    newconnectiondialog.ui \
    chatwindow.ui

QMAKE_CXXFLAGS += -static -lpthread -static-libgcc -static-libstdc++
