QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addservicedialog.cpp \
    infodialog.cpp \
    main.cpp \
    mainwindow.cpp \
    openingwindow.cpp \
    searchdialog.cpp \
    updatedialog.cpp

HEADERS += \
    ServiceEntry.h \
    addservicedialog.h \
    infodialog.h \
    mainwindow.h \
    openingwindow.h \
    searchdialog.h \
    updatedialog.h

FORMS += \
    addservicedialog.ui \
    infodialog.ui \
    mainwindow.ui \
    openingwindow.ui \
    searchdialog.ui \
    updatedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    img/1.jpg
