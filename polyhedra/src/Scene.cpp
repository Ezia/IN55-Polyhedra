#include "Scene.h"

#include "Cube.h"
#include "Sphere.h"
#include "FaceShrinkingFilter.h"


void Scene::init()
{
    initializeOpenGLFunctions();

    // shaders
    m_renderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/render.vsh");
    m_renderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/render.fsh");
    m_renderProgram.link();

    m_shadowProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shadow.vsh");
    m_shadowProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shadow.fsh");
    m_shadowProgram.link();

    m_basicProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/basic.vsh");
    m_basicProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/basic.fsh");
    m_basicProgram.link();

    /************************************************/
    // Hard code here every objects that compose the scene
    /************************************************/

    // small cube
    Cube* cube = new Cube;
    cube->setColor(GREEN);
    FaceShrinkingFilter* faceSkrinkingFilter = new FaceShrinkingFilter();
    faceSkrinkingFilter->setInput(cube);
    faceSkrinkingFilter->setFactor(0.5);
    faceSkrinkingFilter->update();
    Cube* filteredCube = (Cube*) faceSkrinkingFilter->getOutput();
    m_objects.append(filteredCube);

    // base surface
    Cube* cube2  = new Cube;
    cube2->setPosition({0, 0, -1});
    cube2->setDimension({10, 10, 0.5});
    cube2->setColor(BLUE);
    m_objects.append(cube2);

    // another cube
    Cube* cube3 = new Cube;
    cube3->setPosition({-1.1, 0, 0});
    cube3->setDimension({1, 0.5, 0.5});
    cube3->setColor(YELLOW);
    m_objects.append(cube3);

    // a sphere
//    Sphere* sphere1 = new Sphere;
//    sphere1->setPosition({-1., 0, 1.});
//    sphere1->setRadius(1.);
//    sphere1->setXYResolution(8);
//    sphere1->setXZResolution(4);
//    sphere1->setColor(GREEN);
//    m_objects.append(sphere1);

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
    m_spotLight.setShadowTextureBias(0.005);
}

void Scene::drawRender()
{
    drawShadow();

    m_renderProgram.bind();

    glViewport(m_viewPortPosition[0], m_viewPortPosition[1], m_viewPortDimension[0], m_viewPortDimension[1]);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_spotLight.getShadowTexture()->texture());
    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_renderProgram.setUniformValue("mvp_matrix", m_projectionMatrix * m_viewMatrix);
    m_renderProgram.setUniformValue("matrixMV", m_viewMatrix);
    m_renderProgram.setUniformValue("spotLightAmbiant", m_spotLight.getAmbiant());
    m_renderProgram.setUniformValue("spotLightDiffusion", m_spotLight.getDiffuse());
    m_renderProgram.setUniformValue("spotLightSpecular", m_spotLight.getSpecular());
    m_renderProgram.setUniformValue("spotLightPosition", m_spotLight.getPosition());
    m_renderProgram.setUniformValue("spotLightMVP", m_spotLight.getProjection());
    m_renderProgram.setUniformValue("shadowBias", m_spotLight.getShadowTextureBias());

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i]->drawRender(&m_renderProgram);
    }

    m_renderProgram.release();
}

void Scene::drawShadow()
{
    if (!m_shadowTextureComputed) {
        m_shadowProgram.bind();

        m_shadowProgram.setUniformValue("spotLightMVP", m_spotLight.getProjection());

        m_spotLight.getShadowTexture()->bind();

        glViewport(0, 0, m_spotLight.getShadowTexture()->width(), m_spotLight.getShadowTexture()->height());

        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (int i = 0; i < m_objects.size(); i++) {
            m_objects[i]->drawShadow(&m_shadowProgram);
        }

        m_spotLight.getShadowTexture()->release();

        m_shadowProgram.release();

        m_shadowTextureComputed = true;
    }
}

void Scene::drawBasic()
{
    m_basicProgram.bind();

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(m_viewPortPosition[0], m_viewPortPosition[1], m_viewPortDimension[0], m_viewPortDimension[1]);

    m_basicProgram.setUniformValue("MVP", m_projectionMatrix * m_viewMatrix);

    for (int i = 0; i < m_objects.size(); i++) {
        m_objects[i]->drawBasic(&m_basicProgram);
    }

    m_basicProgram.release();
}
