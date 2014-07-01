QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualizer
TEMPLATE = lib

SOURCES += \
    GraphsWindow.cpp \
    InfoTableModel.cpp \
    ModelVisualizer.cpp \
    QSatelliteItem.cpp \
    QStationItem.cpp

HEADERS  += \
    GraphsWindow.h \
    InfoTableModel.h \
    ModelVisualizer.h \
    QSatelliteItem.h \
    QStationItem.h

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    Resources.qrc
