
CONFIG -= release
CONFIG += debug
CONFIG += warn_on

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = password-sticky-note
TEMPLATE = app

unix:MOC_DIR = .moc/
unix:OBJECTS_DIR = .objects/
unix:UI_DIR = .ui/

# Required for using PKGCONFIG variable, and we use PKGCONFIG to get openssl
CONFIG += link_pkgconfig
PKGCONFIG += openssl

QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Werror

RESOURCES += icons/icons.qrc

SOURCES += main.cpp \
        mainwindow.cpp \

HEADERS  += mainwindow.h \
        logger.h

FORMS    += mainwindow.ui

