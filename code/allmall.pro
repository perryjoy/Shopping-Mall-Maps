QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg
qtHaveModule(opengl): QT += opengl


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core\main.cpp \
    device/map.cpp \
    device/svgview.cpp \
    device\mainwindow.cpp

HEADERS += \
    device/map.h \
    device/svgview.h \
    device\mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
