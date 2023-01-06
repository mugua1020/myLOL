QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ai.cpp \
    aicontroller.cpp \
    algorithm.cpp \
    animation.cpp \
    base.cpp \
    character.cpp \
    characterlabel.cpp \
    characterrole.cpp \
    gamelabel.cpp \
    gamemap.cpp \
    gamescene.cpp \
    guidescene.cpp \
    main.cpp \
    mainscene.cpp \
    playingmenu.cpp \


HEADERS += \
    ai.h \
    aicontroller.h \
    algorithm.h \
    animation.h \
    base.h \
    character.h \
    characterlabel.h \
    characterrole.h \
    config.h \
    gamelabel.h \
    gamemap.h \
    gamescene.h \
    guidescene.h \
    mainscene.h \
    playingmenu.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    music.qrc \
    pic.qrc

RC_ICONS += \
    lol.ico

DISTFILES +=

CONFIG += resources_big
