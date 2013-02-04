TEMPLATE = lib

CONFIG -= qt

DEFINES *= UTILITIES_EXPORT

HEADERS *= $$PWD/utilities.h \
           $$PWD/utilities-enums.h \
           $$PWD/utilities-thread.h \
           $$PWD/utilities-mutex.h

SOURCES *= $$PWD/utilities.cpp \
           $$PWD/utilities-thread.cpp

unix{
HEADERS *= $$PWD/utilities-linux.h

SOURCES *= $$PWD/utilities-linux.cpp \
           $$PWD/utilities-thread-linux.cpp \
           $$PWD/utilities-mutex-linux.cpp
}

win32{
HEADERS *= $$PWD/utilities-windows.h

SOURCES *= $$PWD/utilities-windows.cpp \
           $$PWD/utilities-thread-windows.cpp \
           $$PWD/utilities-mutex-windows.cpp
}

INSTALL_LIB_PATH = $$PWD/../
include($$PWD/../3rdparty/common-qmake/pri/installlib.pri)
