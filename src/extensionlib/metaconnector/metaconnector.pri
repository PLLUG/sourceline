CONFIG += c++11

SOURCES += \
    $$PWD/apiclient.cpp \
    $$PWD/apiprovider.cpp \
    $$PWD/publictestinterface.cpp \
    $$PWD/testinerface.cpp \
    $$PWD/invocationbased.cpp \
    $$PWD/remoteapiclient.cpp \
    $$PWD/remoteapiprovider.cpp

HEADERS += \
    $$PWD/apiclient.h \
    $$PWD/apiprovider.h \
    $$PWD/publictestinterface.h \
    $$PWD/testinerface.h \
    $$PWD/genericargumentholder.h \
    $$PWD/typedgenericargumentholder.h \
    $$PWD/typedgenericreturnargumentholder.h \
    $$PWD/genericreturnargumentholder.h \
    $$PWD/invocationbased.h \
    $$PWD/remoteapiclient.h \
    $$PWD/remoteapiprovider.h

HEADERS += $$PWD/genericargumentholder.h
