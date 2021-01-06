# Flappy Bird Qt
# github.com/fuzun/flappy-bird-qt

QT += core gui opengl multimedia
QT -= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flappy-Bird-Qt
TEMPLATE = app

VERSION = 1.5.2

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/source

INCLUDEPATH += \ # submodules
               $$PWD/source/tiny-dnn \
               $$PWD/source/strobe-api/strobe

win32:RC_ICONS += assets/icon.ico

CONFIG += c++14

SOURCES += \
    bird/bird.cpp \
    button/button.cpp \
    game/game.cpp \
    main.cpp \
    mainwindow/mainwindow.cpp \
    physics/physics.cpp \
    scene/scene.cpp \
    view/view.cpp

HEADERS += \
    bird/bird.h \
    button/button.h \
    common.h \
    game/game.h \
    mainwindow/mainwindow.h \
    physics/physics.h \
    scene/scene.h \
    view/view.h

RESOURCES += \
    assets/Resource.qrc
