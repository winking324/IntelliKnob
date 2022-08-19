QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    # Info.plist
    QMAKE_INFO_PLIST = Info.plist

    # Icon
#     ICON = icon.icns
}

include(gitversion.pri)

SOURCES += \
    src/device_dialog.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/preferences_dialog.cpp \
    src/tray_menu.cpp

HEADERS += \
    src/device_dialog.h \
    src/main_window.h \
    src/preferences_dialog.h \
    src/tray_menu.h

RESOURCES += \
    IntelliAgent.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
