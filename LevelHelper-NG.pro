#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T14:49:55
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LevelHelper-NG
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customproperties.cpp \
    graphwidget.cpp \
    supportingcode.cpp \
    leveleditor.cpp \
    sprite.cpp

HEADERS  += mainwindow.h \
    leveleditor.h \
    customproperties.h \
    graphwidget.h \
    supportingcode.h \
    Debug.h \
    sprite.h

FORMS    += mainwindow.ui \
    leveleditor.ui \
    customproperties.ui \
    supportingcode.ui

OTHER_FILES += \
    README.md
