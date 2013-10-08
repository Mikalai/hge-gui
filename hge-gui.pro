QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG -= QT
TARGET = hge-gui

DEFINES += PLATFORM_UNIX

LIBS += -L"/home/mikalaj/develop/hge-unix/build/src/core" -lhge
LIBS += -L"/home/mikalaj/develop/hge-unix/build/src/core" -lhge_helpers

INCLUDEPATH += /home/mikalaj/develop/hge-unix/include

SOURCES += main.cpp \
    src/action.cpp \
    src/signal.cpp \
    src/widget.cpp \
    src/render_adapter.cpp \
    src/hge_render.cpp \
    src/gui_manager.cpp

HEADERS += \
    src/action.h \
    src/signal.h \
    src/widget.h \
    src/render_adapter.h \
    src/hge_render.h \
    src/module.h \
    src/desktop_adapter.h \
    src/gui_manager.h

