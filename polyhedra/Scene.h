#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QOpenGLShaderProgram>

#include "Light.h"

class Scene
{
public:
    Scene();

    void init();

    void draw(QOpenGLShaderProgram *program);
    void drawShadow(QOpenGLShaderProgram *program);

private:
    QList<Polyhedron> m_objects;
    Light m_light;
};

#endif // SCENE_H
