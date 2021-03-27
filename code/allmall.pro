QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg
qtHaveModule(opengl): QT += opengl


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/graph.cpp \
    core/viewer.cpp \
    core/main.cpp \
    device/map.cpp \
    device/svgview.cpp \
    device/mainwindow.cpp \
    shops_data.cpp

HEADERS += \
    core/manager.h \
    device/graph.h \
    device/map.h \
    device/svgview.h \
    device/viewer.h \
    device\mainwindow.h \
    shops_data.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
