QT       += core gui widgets

TARGET = cube
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Polyhedron.cpp \
    Cube.cpp \
    PolyhedronDrawer.cpp \
    FaceShrinkerPolyhedronFilter.cpp \
    Scene.cpp \
    Light.cpp \
    mainwidget.cpp

#qtHaveModule(opengl) {
    QT += opengl

    SOURCES +=

    HEADERS +=

    RESOURCES += \
        shaders.qrc \
        textures.qrc
#}

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
#INSTALLS += target

simulator: warning(This example might not fully work on Simulator platform)

HEADERS += \
    Polyhedron.h \
    Cube.h \
    PolyhedronDrawer.h \
    FaceShrinkerPolyhedronFilter.h \
    Scene.h \
    Light.h \
    mainwidget.h
