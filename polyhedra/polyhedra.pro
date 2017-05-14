QT       += core gui widgets

TARGET = polyhedra
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050800

SOURCES += main.cpp \
    Polyhedron.cpp \
    Cube.cpp \
    PolyhedronDrawer.cpp \
    FaceShrinkerPolyhedronFilter.cpp \
    Scene.cpp \
    Light.cpp \
    mainwidget.cpp \
    mvpmatrix.cpp \
    spotlight.cpp

#qtHaveModule(opengl) {
    QT += opengl

    SOURCES +=

    HEADERS += \
    mvpmatrix.h \
    spotlight.h

    RESOURCES += \
        shaders.qrc \
        textures.qrc \
    vshadershadowmap.vsh \
    fshadershadowmap.fsh

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
