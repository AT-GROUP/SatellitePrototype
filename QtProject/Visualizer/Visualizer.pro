QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualizer
TEMPLATE = lib

SOURCES += \
    ../../src/Visualizer/ConfigDialog.cpp \
    ../../src/Visualizer/ConfigPages.cpp \
    ../../src/Visualizer/InfoTableModel.cpp \
    ../../src/Visualizer/ModelVisualizer.cpp \
    ../../src/Visualizer/QSatelliteItem.cpp \
    ../../src/Visualizer/QStationItem.cpp
HEADERS  += \
    ../../src/Visualizer/ConfigDialog.h \
    ../../src/Visualizer/ConfigPages.h \
    ../../src/Visualizer/InfoTableModel.h \
    ../../src/Visualizer/ModelVisualizer.h \
    ../../src/Visualizer/QSatelliteItem.h \
    ../../src/Visualizer/QStationItem.h

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    ../../src/Visualizer/Resources.qrc
