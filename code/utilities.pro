TEMPLATE = lib

CONFIG -= qt

DEFINES *= UTILITIES_EXPORT

HEADERS *= $$PWD/utilities-enums.h \
           $$PWD/utilities-thread.h \
           $$PWD/utilities-mutex.h \
           $$PWD/utilities-callback.h \
           $$PWD/utilities-socket.h \
           $$PWD/utilities-math.h \
           $$PWD/utilities-string.h \
           $$PWD/utilities-importexport.h \
           $$PWD/utilities-time.h \
           $$PWD/utilities-keyboard.h \
           $$PWD/utilities-screen.h \
           $$PWD/utilities-file.h \
           $$PWD/utilities-tokenizer.h \
           $$PWD/utilities-stringrpc.h \
           $$PWD/utilities-cli-menu.h \
           $$PWD/utilities-logger.h

SOURCES *= $$PWD/utilities-thread.cpp \
           $$PWD/utilities-callback.cpp \
           $$PWD/utilities-socket.cpp \
           $$PWD/utilities-math.cpp \
           $$PWD/utilities-string.cpp \
           $$PWD/utilities-tokenizer.cpp \
           $$PWD/utilities-stringrpc.cpp \
           $$PWD/utilities-screen.cpp \
           $$PWD/utilities-cli-menu.cpp \
           $$PWD/utilities-logger.cpp \
           $$PWD/utilities-time.cpp

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
