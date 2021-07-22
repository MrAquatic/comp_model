QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Demo.cpp \
    main.cpp \
    MainWindow.cpp \
    ParticleAnimation.cpp \
    Particle.cpp \
    PictureBox.cpp \
    Test.cpp \
    Theory.cpp

HEADERS += \
    Demo.h \
    TextLoader.h \
    MainWindow.h \
    ParticleAnimation.h \
    Particle.h \
    PictureBox.h \
    Test.h \
    Theory.h

FORMS += \
    Demo.ui \
    MainWindow.ui \
    Test.ui \
    Theory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
