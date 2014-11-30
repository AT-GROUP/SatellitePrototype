#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T19:55:40
#
#-------------------------------------------------

QT       -= gui
QT       += concurrent

TARGET = SNMP
TEMPLATE = lib

DEFINES += SNMP_LIBRARY

SOURCES += \
    ../../src/SNMP/RouterPool.cpp \
    ../../src/SNMP/SnmpRouter.cpp \
    ../../src/SNMP/RealWorld.cpp \
    ../../src/SNMP/RealStation.cpp \
    ../../src/SNMP/RealSatellite.cpp

HEADERS += \
    ../../src/SNMP/RouterPool.h \
    ../../src/SNMP/SnmpRouter.h \
    ../../src/SNMP/RealWorld.h \
    ../../src/SNMP/RealStation.h \
    ../../src/SNMP/RealSatellite.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++11
