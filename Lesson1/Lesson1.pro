QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    discriminant.cpp \
    main.cpp \
    mainwindow.cpp \
    triangl.cpp \
    worktext.cpp

HEADERS += \
    discriminant.h \
    mainwindow.h \
    triangl.h \
    worktext.h

FORMS += \
    discriminant.ui \
    mainwindow.ui \
    triangl.ui \
    worktext.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
