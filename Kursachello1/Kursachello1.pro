#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T18:13:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursachello1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    regElement.cpp \
    regCompare.cpp \
    MonitorWidget.cpp \
    ComparisonWidget.cpp \
    RegThread.cpp \
    RegistryExportWidget.cpp

HEADERS  += mainwindow.h \
    regCompare.h \
    regElement.h \
    MonitorWidget.h \
    ComparisonWidget.h \
    RegThread.h \
    RegistryExportWidget.h

FORMS    += mainwindow.ui \
    MonitorWidget.ui \
    ComparisonWidget.ui \
    RegistryExportWidget.ui
