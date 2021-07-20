QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    demo.cpp \
    electron.cpp \
    main.cpp \
    mainwindow.cpp \
    n_semiconductor.cpp \
    particle.cpp \
    picturebox.cpp \
    test.cpp \
    theory.cpp

HEADERS += \
    demo.h \
    electron.h \
    loader.h \
    mainwindow.h \
    n_semiconductor.h \
    particle.h \
    picturebox.h \
    test.h \
    theory.h

FORMS += \
    demo.ui \
    mainwindow.ui \
    test.ui \
    theory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
