QT += core gui widgets

TARGET = polyhedra
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050800

INCLUDEPATH += src

SOURCES += \
    src/Cube.cpp \
    src/Polyhedron.cpp \
    src/Scene.cpp \
    src/SpotLight.cpp \
    src/MainWidget.cpp \
    src/Main.cpp \
    src/FaceShrinkingFilter.cpp \
    src/Sphere.cpp

    HEADERS += \
    src/Cube.h \
    src/Polyhedron.h \
    src/Scene.h \
    src/SpotLight.h \
    src/MainWidget.h \
    src/PolyhedronFilter.h \
    src/FaceShrinkingFilter.h \
    src/Sphere.h

    RESOURCES += \
        shaders.qrc

    QT += opengl
