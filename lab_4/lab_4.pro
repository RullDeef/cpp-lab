QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cabin.cpp \
    cabinwidget.cpp \
    controller.cpp \
    controllerbutton.cpp \
    controllerbuttonwidget.cpp \
    controllerwidget.cpp \
    door.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cabin.h \
    cabinwidget.h \
    common.h \
    controller.h \
    controllerbutton.h \
    controllerbuttonwidget.h \
    controllerwidget.h \
    door.h \
    mainwindow.h

FORMS += \
    cabinwidget.ui \
    controllerwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
