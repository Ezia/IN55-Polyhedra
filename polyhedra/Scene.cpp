#include "Scene.h"

#include "PolyhedronDrawer.h"
#include "Cube.h"
#include "FaceShrinkerPolyhedronFilter.h"


Scene::Scene()
{
}

void Scene::init()
{
    initializeOpenGLFunctions();

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
    m_spotLight.setDirection({-1, 0, -1});
    m_spotLight.setUpDirection({0, 0, 1});
    m_spotLight.setPosition({1, -1, 3});
    m_spotLight.setHorizontalAngle(60);
    m_spotLight.setVerticalAngle(40);
    m_spotLight.setPixelPerDegree(40);
    m_spotLight.setNearPlan(0.5);
    m_spotLight.setFarPlan(15);
    m_spotLight.setAmbiant({0.1, 0.1, 0.1});
    m_spotLight.setDiffuse({0.8, 0.8, 0.8});
    m_spotLight.setSpecular({1, 1, 1});
}

void Scene::draw(QOpenGLShaderProgram *program)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_spotLight.getShadowTexture()->texture());
    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    program->setUniformValue("spotLightAmbiant", m_spotLight.getAmbiant());
    program->setUniformValue("spotLightDiffusion", m_spotLight.getDiffuse());
    program->setUniformValue("spotLightSpecular", m_spotLight.getSpecular());
    program->setUniformValue("spotLightPosition", m_spotLight.getPosition());

    program->setUniformValue("spotLightMVP", m_spotLight.getProjection());

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawRender(program);
    }

}

void Scene::drawShadow(QOpenGLShaderProgram *program)
{
    program->setUniformValue("spotLightMVP", m_spotLight.getProjection());

    m_spotLight.getShadowTexture()->bind();

    glViewport(0, 0, m_spotLight.getShadowTexture()->width(), m_spotLight.getShadowTexture()->height());

    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_CULL_FACE);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawShadow(program);
    }

    m_spotLight.getShadowTexture()->release();
}

void Scene::drawTest(QOpenGLShaderProgram *program)
{
    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i].drawTest(program);
    }
}
