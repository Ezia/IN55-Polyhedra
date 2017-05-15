#include "Scene.h"

#include "PolyhedronDrawer.h"
#include "Cube.h"
#include "FaceShrinkerPolyhedronFilter.h"


Scene::Scene()
{
}

void Scene::init()
{
    /************************************************/
    // Hard code here every components that compose the scene
    /************************************************/

    // small cube
    Cube cube;
    cube.update();
    m_objects.append(cube);
    m_objects[0].setColor(GREEN);

    // base surface
    Cube cube2;
    cube2.setPosition({0, 0, -1});
    cube2.setDimension({10, 10, 0.5});
    cube2.update();
    m_objects.append(cube2);
    m_objects[1].setColor(BLUE);


    // spot light
    m_spotLight.setDirection({0, -1, -1});
    m_spotLight.setUpDirection({0, 1, 0});
    m_spotLight.setPosition({1, -1, 3});
    m_spotLight.update();
}

void Scene::draw(QOpenGLShaderProgram *program, QMatrix4x4 proj)
{
    QVector3D ambiant, diffusion;
    ambiant = {0.2, 0.2, 0.2};
    diffusion = {0.8, 0.8, 0.8};
    program->setUniformValue("spotLightAmbiant", ambiant);
    program->setUniformValue("spotLightDiffusion", diffusion);

    program->setUniformValue("spotLightMVP", proj * m_spotLight.getProjection());

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawRender(program);
    }

}

void Scene::drawShadow(QOpenGLShaderProgram *program, QMatrix4x4 viewProjectionMatrix)
{
    program->setUniformValue("spotLightMVP", viewProjectionMatrix * m_spotLight.getProjection());

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawShadow(program);
    }
}

void Scene::drawTest(QOpenGLShaderProgram *program)
{
    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawTest(program);
    }
}
