QT       += core gui widgets

TARGET = cube
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Polyhedron.cpp \
    Cube.cpp \
    PolyhedronDrawer.cpp \
    MainWidget.cpp \
    FaceShrinkerPolyhedronFilter.cpp \
    Scene.cpp \
    Light.cpp \
    soil/src/image_DXT.c \
    soil/src/image_helper.c \
    soil/src/SOIL.c \
    soil/src/stb_image_aug.c

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
    MainWidget.h \
    FaceShrinkerPolyhedronFilter.h \
    Scene.h \
    Light.h \
    soil/src/image_DXT.h \
    soil/src/image_helper.h \
    soil/src/SOIL.h \
    soil/src/stb_image_aug.h \
    soil/src/stbi_DDS_aug.h \
    soil/src/stbi_DDS_aug_c.h
