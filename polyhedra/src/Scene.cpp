#include "Scene.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

#include "Cube.h"
#include "Sphere.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Scene::Scene() :
    m_objects(),
    m_spotLight(),
    m_shadowTextureComputed(false),
    m_viewMatrix(),
    m_projectionMatrix(),
    m_viewPortPosition(),
    m_viewPortDimension()
{}

Scene::~Scene() {
    for (int32 i = 0; i < m_objects.size(); i++)
    {
        delete m_objects[i];
    }

    foreach (FaceShrinkingFilter* filter, m_filters)
    {
        delete filter->getInput();
        delete filter;
    }
}

//============================= ATTRIBUTE ACCESSORS ==========================

QMatrix4x4 Scene::getViewMatrix() const
{
    return m_viewMatrix;
}

QMatrix4x4 Scene::getProjectionMatrix() const
{
    return m_viewMatrix;
}

QVector2D Scene::getViewPortDimension() const
{
    return m_viewPortDimension;
}

QVector2D Scene::getViewPortPosition() const
{
    return m_viewPortPosition;
}

void Scene::setViewMatrix(QMatrix4x4 viewMatrix)
{
    m_viewMatrix = viewMatrix;
}

void Scene::setProjectionMatrix(QMatrix4x4 projectionMatrix)
{
    m_projectionMatrix = projectionMatrix;
}

void Scene::setViewPortPosition(QVector2D viewPortPosition)
{
    m_viewPortPosition = viewPortPosition;
}

void Scene::setViewPortDImension(QVector2D viewPortDimension)
{
    m_viewPortDimension = viewPortDimension;
}

void Scene::notifyShadowMapNeedsComputation()
{
    m_shadowTextureComputed = false;
}

//============================= OPERATIONS ===================================


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
    Cube* cube1 = new Cube;
    cube1->setPosition({2.5, 0, 0.5});
    cube1->setDimension({2, 2, 2});
    cube1->setGeometryColor(PURPLE);
    FaceShrinkingFilter* cube1Filter = new FaceShrinkingFilter();
    cube1Filter->setInput(cube1);
    cube1Filter->setFactor(0.5);
    cube1Filter->update();
//    Cube* filteredCube1 = (Cube*) cube1Filter->getOutput();
    m_filters.append(cube1Filter);

    // base surface
    Cube* cube2  = new Cube;
    cube2->setPosition({0, 0, -1});
    cube2->setDimension({10, 10, 0.5});
    cube2->setGeometryColor(BLUE);
    m_objects.append(cube2);

    // another cube
    Cube* cube3 = new Cube;
    cube3->setPosition({-2.5, 0, 0});
    cube3->setDimension({2, 1, 1});
    cube3->setGeometryColor(YELLOW);
    FaceShrinkingFilter* cube3Filter = new FaceShrinkingFilter();
    cube3Filter->setInput(cube3);
    cube3Filter->setFactor(0.5);
    cube3Filter->update();
    m_filters.append(cube3Filter);

    // a sphere
    Sphere* sphere1 = new Sphere;
    sphere1->setPosition({0, 0, 0.5});
    sphere1->setRadius(1.);
    sphere1->setXYResolution(50);
    sphere1->setXZResolution(20);
    sphere1->setGeometryColor(GREEN);
    FaceShrinkingFilter* sphere1Filter = new FaceShrinkingFilter();
    sphere1Filter->setInput(sphere1);
    sphere1Filter->setFactor(0.5);
    sphere1Filter->update();
    m_filters.append(sphere1Filter);

    // spot light
    m_spotLight.setDirection({0, 0, -1});
    m_spotLight.setUpDirection({0, 1, 0});
    m_spotLight.setPosition({0, 0, 5});
    m_spotLight.setHorizontalAngle(120);
    m_spotLight.setVerticalAngle(120);
    m_spotLight.setPixelPerDegree(40);
    m_spotLight.setNearPlan(0.5);
    m_spotLight.setFarPlan(15);
    m_spotLight.setAmbiant({0.2, 0.2, 0.2});
    m_spotLight.setDiffuse({0.6, 0.6, 0.6});
    m_spotLight.setSpecular({1., 1., 1.});
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
    m_renderProgram.setUniformValue("invMatrixMV", m_viewMatrix.inverted());
    m_renderProgram.setUniformValue("spotLightAmbiant", m_spotLight.getAmbiant());
    m_renderProgram.setUniformValue("spotLightDiffusion", m_spotLight.getDiffuse());
    m_renderProgram.setUniformValue("spotLightSpecular", m_spotLight.getSpecular());
    m_renderProgram.setUniformValue("spotLightPosition", m_spotLight.getPosition());
    m_renderProgram.setUniformValue("spotLightMVP", m_spotLight.getProjection());
    m_renderProgram.setUniformValue("shadowBias", m_spotLight.getShadowTextureBias());

    for (int32 i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->drawRender(&m_renderProgram);
    }

    foreach (FaceShrinkingFilter* filter, m_filters)
    {
        filter->getOutput()->drawRender(&m_renderProgram);
    }

    m_renderProgram.release();
}

void Scene::drawShadow()
{
    if (!m_shadowTextureComputed)
    {
        m_shadowProgram.bind();

        m_shadowProgram.setUniformValue("spotLightMVP", m_spotLight.getProjection());

        m_spotLight.getShadowTexture()->bind();

        glViewport(0, 0, m_spotLight.getShadowTexture()->width(), m_spotLight.getShadowTexture()->height());

        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (int32 i = 0; i < m_objects.size(); i++)
        {
            m_objects[i]->drawShadow(&m_shadowProgram);
        }

        foreach (FaceShrinkingFilter* filter, m_filters)
        {
            filter->getOutput()->drawShadow(&m_shadowProgram);
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

    for (int32 i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->drawBasic(&m_basicProgram);
    }

    foreach (FaceShrinkingFilter* filter, m_filters)
    {
        filter->getOutput()->drawBasic(&m_basicProgram);
    }

    m_basicProgram.release();
}

QList<Polyhedron*> Scene::getObjectList() const
{
    return this->m_objects;
}

QList<FaceShrinkingFilter*> Scene::getFilterList() const
{
    return this->m_filters;
}

SpotLight* Scene::getSpotLight()
{
    return &(this->m_spotLight);
}


