#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T16:49:45
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

DEFINES += USETHREADPOOL

TARGET = qmlwebmodelserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qhttp.cpp \
    qhttpauthenticator.cpp \
    serverthread.cpp \
    slotsocket.cpp \
    requestparser.cpp \
    threadedtcpserver.cpp \
    modelmapper.cpp \
    mimetypemapper.cpp \
    csvmodel.cpp \
    singleton.cpp

HEADERS += \
    qhttp.h \
    qhttpauthenticator_p.h \
    serverthread.h \
    qringbuffer_p.h \
    slotsocket.h \
    requestparser.h \
    threadedtcpserver.h \
    modelmapper.h \
    mimetypemapper.h \
    csvmodel.h \
    singleton.h

OTHER_FILES += \
    sample.json
