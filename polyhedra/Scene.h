#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QGLShaderProgram>

#include "Light.h"

class Scene
{
public:
    Scene();

    void init();

    void draw(QGLShaderProgram *program);
    void drawShadow(QGLShaderProgram *program);

private:
    QList<Polyhedron> m_objects;
    Light m_light;
};

#endif // SCENE_H
