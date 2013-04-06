INCLUDEPATH *= $$PWD/include

LIBS *= -L$$PWD/lib \
        -lutilities

libs.path = $$target.path
libs.files = $$PWD/lib/utilities.dll
INSTALLS *= libs