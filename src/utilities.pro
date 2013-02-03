TEMPLATE = lib

CONFIG -= qt

DEFINES *= UTILITIES_EXPORT

HEADERS *= utilities.h \
           utilities-enums.h \
           utilities-thread.h \
           utilities-mutex.h

SOURCES *= utilities.cpp \
           utilities-thread.cpp

unix{
HEADERS *= utilities-linux.h

SOURCES *= utilities-linux.cpp \
           utilities-thread-linux.cpp \
           utilities-mutex-linux.cpp
}

win32{
HEADERS *= utilities-windows.h

SOURCES *= utilities-windows.cpp \
           utilities-thread-windows.cpp \
           utilities-mutex-windows.cpp
}

INSTALL_LIB_PATH = ../../
include(../installlib.pri)
