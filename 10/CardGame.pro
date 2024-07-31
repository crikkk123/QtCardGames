QT       += core gui multimedia
QT += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationwindow.cpp \
    bgmcontrol.cpp \
    buttongroup.cpp \
    card.cpp \
    cardpanel.cpp \
    cards.cpp \
    countdown.cpp \
    endingpanel.cpp \
    gamecontrol.cpp \
    main.cpp \
    gamepanel.cpp \
    mybutton.cpp \
    player.cpp \
    playhand.cpp \
    robot.cpp \
    robotgraplord.cpp \
    robotplayhand.cpp \
    scorepanel.cpp \
    strategy.cpp \
    userplayer.cpp

HEADERS += \
    animationwindow.h \
    bgmcontrol.h \
    buttongroup.h \
    card.h \
    cardpanel.h \
    cards.h \
    countdown.h \
    endingpanel.h \
    gamecontrol.h \
    gamepanel.h \
    mybutton.h \
    player.h \
    playhand.h \
    robot.h \
    robotgraplord.h \
    robotplayhand.h \
    scorepanel.h \
    strategy.h \
    userplayer.h

FORMS += \
    buttongroup.ui \
    gamepanel.ui \
    scorepanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc