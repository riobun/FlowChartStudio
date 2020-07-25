QT       += core gui

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
    action.cpp \
    arrow.cpp \
    changeelementaction.cpp \
    diamond.cpp \
    editelementaction.cpp \
    flowchartscene.cpp \
    graph.cpp \
    graphelement.cpp \
    groupaction.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    nodeevents.cpp \
    nodeitem.cpp \
    rectangle.cpp\
    text.cpp \

HEADERS += \
    action.h \
    arrow.h \
    changeelementaction.h \
    diamond.h \
    editelementaction.h \
    elementProperty.h \
    elementshape.h \
    flowchartscene.h \
    graph.h \
    graphelement.h \
    groupaction.h \
    idpool.h \
    mainwindow.h \
    node.h \
    nodeevents.h \
    nodeitem.h \
    rectangle.h\
    text.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
