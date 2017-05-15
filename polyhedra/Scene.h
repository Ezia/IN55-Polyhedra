#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QOpenGLShaderProgram>
#include "mvpmatrix.h"

#include "spotlight.h"

class Scene
{
public:
    Scene();

    // Scene building
    // Objects and light are hard coded here for testing purpose
    void init();

    // draw the scene objects
    void draw(QOpenGLShaderProgram *program, QMatrix4x4 proj);

    // draw a shadow map from the spot light point of view
    // TODO : remove VPMatrix parameter and use light parameters
    void drawShadow(QOpenGLShaderProgram *program, QMatrix4x4 viewProjectionMatrix);

    void drawTest(QOpenGLShaderProgram* program);

private:
    // objects in the scene
    QList<Polyhedron> m_objects;

    // spot light of the scene
    // TODO : develop other kinds of light
    SpotLight m_spotLight;
};

#endif // SCENE_H
