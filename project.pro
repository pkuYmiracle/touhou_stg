QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/action.hpp \
    game/bonus.cpp \
    game/bullet.cpp \
    game/bulletgroup.cpp \
    game/bulletprototype.cpp \
    game/enemy.cpp \
    game/enemyprototype.cpp \
    game/entity.cpp \
    game/gamecontroller.hpp \
    game/livingentity.cpp \
    game/player.cpp \
    game_board.cpp \
    game/keyboardhandler.hpp \
    level_menu.cpp \
    main.cpp \
    baseboard.cpp \
    mypushbottom.cpp \
    select_level.cpp \
    startboard.cpp \

HEADERS += \
    game/bonus.h \
    game/bullet.h \
    game/bulletgroup.h \
    game/bulletprototype.h \
    game/enemy.h \
    game/config.h \
    game/enemyprototype.h \
    game/entity.h \
    game/livingentity.h \
    game/player.h \
    game_board.h \
    level_menu.h \
    mypushbottom.h \
    select_level.h \
    startboard.h \
    baseboard.h \

FORMS += \
    baseboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc
