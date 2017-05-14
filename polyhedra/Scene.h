#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QOpenGLShaderProgram>
#include "mvpmatrix.h"

#include "Light.h"
#include "spotlight.h"

class Scene
{
public:
    Scene();

    void init();

    void draw(QOpenGLShaderProgram *program, MVPMatrix mvp);
    void drawShadow(QOpenGLShaderProgram *program, MVPMatrix mvp);

private:
    QList<Polyhedron> m_objects;
//    Light m_light;
    SpotLight m_spotLight;
};

#endif // SCENE_H
