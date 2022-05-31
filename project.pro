QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game_board.cpp \
    level_menu.cpp \
    main.cpp \
    baseboard.cpp \
    mypushbottom.cpp \
    select_level.cpp \
    startboard.cpp

HEADERS += \
    baseboard.h \
    game_board.h \
    level_menu.h \
    mypushbottom.h \
    select_level.h \
    startboard.h

FORMS += \
    baseboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc
