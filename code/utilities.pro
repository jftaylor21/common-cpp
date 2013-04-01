TEMPLATE = lib

CONFIG -= qt

DEFINES *= UTILITIES_EXPORT

HEADERS *= $$PWD/utilities.h \
           $$PWD/utilities-enums.h \
           $$PWD/utilities-thread.h \
           $$PWD/utilities-mutex.h \
           $$PWD/utilities-callback.h \
           $$PWD/utilities-socket.h \
           $$PWD/utilities-math.h \
           $$PWD/utilities-conversion.h \
           $$PWD/utilities-importexport.h

SOURCES *= $$PWD/utilities.cpp \
           $$PWD/utilities-thread.cpp \
           $$PWD/utilities-callback.cpp \
           $$PWD/utilities-socket.cpp \
           $$PWD/utilities-math.cpp \
           $$PWD/utilities-conversion.cpp

unix{
HEADERS *= $$PWD/utilities-linux.h

SOURCES *= $$PWD/utilities-linux.cpp \
           $$PWD/utilities-thread-linux.cpp \
           $$PWD/utilities-mutex-linux.cpp \
           $$PWD/utilities-socket-linux.cpp
}

win32{
HEADERS *= $$PWD/utilities-windows.h

SOURCES *= $$PWD/utilities-windows.cpp \
           $$PWD/utilities-thread-windows.cpp \
           $$PWD/utilities-mutex-windows.cpp \
           $$PWD/utilities-socket-windows.cpp
}

win32:LIBS *= -lws2_32

INSTALL_LIB_PATH = $$PWD/../
include($$PWD/3rdparty/common-qmake/pri/installlib.pri)
