QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG -= QT
TARGET = hge-gui

DEFINES += PLATFORM_UNIX

unix:LIBS += -L"/home/mikalaj/develop/hge-unix/build/src/core" -lhge
unix:LIBS += -L"/home/mikalaj/develop/hge-unix/build/src/core" -lhge_helpers
unix:INCLUDEPATH += /home/mikalaj/develop/hge-unix/include

win32:LIBS += d:/the_test/hge181/lib/gcc/libhge.a
win32:LIBS += d:/the_test/hge181/lib/gcc/libhgehelp.a
win32:INCLUDEPATH += d:/the_test/hge181/include



SOURCES += main.cpp \
    src/action.cpp \
    src/signal.cpp \
    src/widget.cpp \
    src/render_adapter.cpp \
    src/hge_render.cpp \
    src/gui_manager.cpp \
    src/style.cpp \
    src/widget_animation.cpp \
    src/button.cpp \
    src/text_line.cpp

HEADERS += \
    src/action.h \
    src/signal.h \
    src/widget.h \
    src/render_adapter.h \
    src/hge_render.h \
    src/module.h \
    src/desktop_adapter.h \
    src/gui_manager.h \
    src/style.h \
    src/widget_animation.h \
    src/button.h \
    src/text_line.h

