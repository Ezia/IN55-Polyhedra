QT       += core gui widgets

TARGET = cube
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Polyhedron.cpp \
    Cube.cpp \
    PolyhedronDrawer.cpp \
    MainWidget.cpp

qtHaveModule(opengl) {
    QT += opengl

    SOURCES +=

    HEADERS +=

    RESOURCES += \
        shaders.qrc \
        textures.qrc
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

simulator: warning(This example might not fully work on Simulator platform)

HEADERS += \
    Polyhedron.h \
    Cube.h \
    PolyhedronDrawer.h \
    MainWidget.h
