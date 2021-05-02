QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    MouseClick.hpp \
    mainwindow.h

FORMS += \
    mainwindow.ui

QMAKE_SPEC_T = $$[QMAKE_SPEC]#see https://stackoverflow.com/questions/25916619/qmake-how-to-figure-out-host-platform-and-target-platform-when-cross-compiling

contains(QMAKE_SPEC_T,.*win32.*){
    HOST_PLATFORM=WIN
    IS_WIN = 1
}

contains(QMAKE_SPEC_T,.*macx.*){
    HOST_PLATFORM=MAC
    IS_MAC = 1
}

contains(QMAKE_SPEC_T,.*linux.*){
    HOST_PLATFORM=LINUX
    IS_LINUX = 1
    QMAKE_LINK += -lX11
}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
