QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Visualizer
TEMPLATE = lib

SOURCES += \
    ../../src/Visualizer/ConfigDialog.cpp \
    ../../src/Visualizer/ConfigPages.cpp \
    ../../src/Visualizer/InfoTableModel.cpp \
    ../../src/Visualizer/ModelVisualizer.cpp \
    ../../src/Visualizer/QSatelliteItem.cpp \
    ../../src/Visualizer/QStationItem.cpp \
    ../../src/Visualizer/StatisticCollector.cpp \
    ../../src/Visualizer/qcustomplot.cpp \
    ../../src/Visualizer/GraphicsWidget.cpp
HEADERS  += \
    ../../src/Visualizer/ConfigDialog.h \
    ../../src/Visualizer/ConfigPages.h \
    ../../src/Visualizer/InfoTableModel.h \
    ../../src/Visualizer/ModelVisualizer.h \
    ../../src/Visualizer/QSatelliteItem.h \
    ../../src/Visualizer/QStationItem.h \
    ../../src/Visualizer/StatisticCollector.h \
    ../../src/Visualizer/qcustomplot.h \
    ../../src/Visualizer/GraphicsWidget.h

RESOURCES += \
    ../../src/Visualizer/Resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Model/release/ -lModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Model/debug/ -lModel
else:unix: LIBS += -L$$OUT_PWD/../Model/ -lModel

INCLUDEPATH += $$PWD/../Model
DEPENDPATH += $$PWD/../Model

QMAKE_CXXFLAGS += -std=c++11
