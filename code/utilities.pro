TEMPLATE = lib

CONFIG -= qt

DEFINES *= UTILITIES_EXPORT

HEADERS *= $$PWD/utilities-enums.h \
           $$PWD/utilities-thread.h \
           $$PWD/utilities-mutex.h \
           $$PWD/utilities-callback.h \
           $$PWD/utilities-socket.h \
           $$PWD/utilities-math.h \
           $$PWD/utilities-conversion.h \
           $$PWD/utilities-importexport.h \
           $$PWD/utilities-time.h \
           $$PWD/utilities-keyboard.h \
           $$PWD/utilities-screen.h \
           $$PWD/utilities-file.h \
           $$PWD/utilities-tokenizer.h

SOURCES *= $$PWD/utilities-thread.cpp \
           $$PWD/utilities-callback.cpp \
           $$PWD/utilities-socket.cpp \
           $$PWD/utilities-math.cpp \
           $$PWD/utilities-conversion.cpp \
           $$PWD/utilities-tokenizer.cpp

unix{
HEADERS *= $$PWD/utilities-screen-linux.h \
           $$PWD/utilities-keyboard-linux.h

SOURCES *= $$PWD/utilities-thread-linux.cpp \
           $$PWD/utilities-mutex-linux.cpp \
           $$PWD/utilities-socket-linux.cpp \
           $$PWD/utilities-time-linux.cpp \
           $$PWD/utilities-keyboard-linux.cpp \
           $$PWD/utilities-screen-linux.cpp \
           $$PWD/utilities-file-linux.cpp
}

win32{
SOURCES *= $$PWD/utilities-thread-windows.cpp \
           $$PWD/utilities-mutex-windows.cpp \
           $$PWD/utilities-socket-windows.cpp \
           $$PWD/utilities-time-windows.cpp \
           $$PWD/utilities-keyboard-windows.cpp \
           $$PWD/utilities-screen-windows.cpp
}

win32:LIBS *= -lws2_32

INSTALL_LIB_PATH = $$PWD/../
include($$PWD/3rdparty/common-qmake/pri/installlib.pri)
