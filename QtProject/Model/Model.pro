TEMPLATE = lib
CONFIG += console qt
CONFIG -= app_bundle

HEADERS += \
    ../../src/Model/resources.h \
    ../../src/Model/satellite.h \
    ../../src/Model/station.h \
    ../../src/Model/model.h

SOURCES += \
    ../../src/Model/model.cpp \
    ../../src/Model/satellite.cpp \
    ../../src/Model/station.cpp

