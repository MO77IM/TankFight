#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T00:54:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trueTank
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
    thing.cpp \
    tank.cpp \
    bullet.cpp \
    stone.cpp \
    metal.cpp \
    shrub.cpp \
    start.cpp \
    gamemap.cpp \
    menu.cpp \
    winjump.cpp \
    losejump.cpp \
    pass.cpp \
    pctank.cpp \
    prop.cpp

HEADERS += \
    thing.h \
    tank.h \
    bullet.h \
    stone.h \
    metal.h \
    shrub.h \
    start.h \
    gamemap.h \
    menu.h \
    winjump.h \
    losejump.h \
    pass.h \
    pctank.h \
    prop.h

FORMS += \
        widget.ui \
    start.ui \
    gamemap.ui \
    menu.ui \
    winjump.ui \
    losejump.ui \
    pass.ui

RESOURCES += \
    rsc.qrc
