QT += widgets
CONFIG += c++11
TEMPLATE = app
TARGET = RainfallTracker

SOURCES += \
    main.cpp \
    Q1/rainrecord.cpp \
    Q2/rainxml.cpp \
    Q3/stationthread.cpp \
    Q3/mytablewidgetmemento.cpp \
    Client/client.cpp

HEADERS += \
    Q1/rainrecord.h \
    Q2/rainxml.h \
    Q3/stationthread.h \
    Q3/mytablewidgetmemento.h \
    Client/client.h
