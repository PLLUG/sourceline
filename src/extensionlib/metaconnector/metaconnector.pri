CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=gnu++0x

SOURCES += \
    $$PWD/apiclient.cpp \
    $$PWD/apiprovider.cpp \
    $$PWD/publictestinterface.cpp \
    $$PWD/testinerface.cpp \
    $$PWD/invocationbased.cpp

HEADERS += \
    $$PWD/apiclient.h \
    $$PWD/apiprovider.h \
    $$PWD/publictestinterface.h \
    $$PWD/testinerface.h \
    $$PWD/genericargumentholder.h \
    $$PWD/typedgenericargumentholder.h \
    $$PWD/typedgenericreturnargumentholder.h \
    $$PWD/genericreturnargumentholder.h \
    $$PWD/invocationbased.h

HEADERS += $$PWD/genericargumentholder.h
