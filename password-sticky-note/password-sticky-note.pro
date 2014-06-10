
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = password-sticky-note
TEMPLATE = app

unix:MOC_DIR = .moc/
unix:OBJECTS_DIR = .objects/
unix:UI_DIR = .ui/

CONFIG += warn_on

# Required for using PKGCONFIG variable, and we use PKGCONFIG to get openssl
CONFIG += link_pkgconfig
PKGCONFIG += openssl

QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Werror

RESOURCES += icons/icons.qrc

SOURCES += main.cpp \
        mainwindow.cpp \
        aes.c \
        aescrypt.c \
        sha256.c \
        password.c \
        keyfile.c \

HEADERS  += mainwindow.h \
        aes.h \
        aescrypt.h \
        sha256.h \
        password.h \
        keyfile.h \
        /usr/include/openssl/aes.h

FORMS    += mainwindow.ui

