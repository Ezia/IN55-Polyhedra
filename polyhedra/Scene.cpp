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

    Cube cube2;
    cube2.setPosition({0, 0, -1});
    cube2.setDimension({10, 10, 0.5});
    cube2.init();
    m_objects.append(cube2);
    m_objects[0].setColor(BLUE);


    Cube cube;
    cube.init();
    m_objects.append(cube);
    m_objects[1].setColor(GREEN);

    //    m_light.setPosition({0, 0, 3});
//    m_light.init();

    m_spotLight.setDirection({0, -1, -1});
    m_spotLight.setUpDirection({0, 1, 0});
    m_spotLight.setPosition({1, -1, 3});
    m_spotLight.update();
}

void Scene::draw(QOpenGLShaderProgram *program, MVPMatrix mvp)
{
    // Set modelview-projection matrix
    program->setUniformValue("mvp_matrix", mvp.projection * mvp.view * mvp.model);
//    program->setUniformValue("mv_matrix", mvp.view * mvp.model);
    program->setUniformValue("spotLightMV", m_spotLight.getProjection());
    program->setUniformValue("spotLightMVP", mvp.projection * m_spotLight.getProjection());

    PolyhedronDrawer drawer;
    drawer.init();
    drawer.setSpotLight(&m_spotLight);
//    drawer.setLight(&m_light);
    for (int i = 0; i < m_objects.size(); i++) {
        drawer.setPolyhedron(&(m_objects[i]));
        drawer.update();
        drawer.draw(program);
    }

//    m_light.update();
//    m_light.draw(program);
}

void Scene::drawShadow(QOpenGLShaderProgram *program, MVPMatrix mvp)
{
    MVPMatrix lightMVP;
    lightMVP.model = mvp.model;
//    lightMVP.view.translate(-m_light.getPosition());
    lightMVP.view.lookAt({0, 0, 0}, {0, -1, -1}, {0, -1, 0});
//    lightMVP.projection.perspective(45, 1, 2, 50);
    lightMVP.projection = mvp.projection;

//    QMatrix4x4 transform;
//    transform.setToIdentity();
//    transform.translate(-m_light.getPosition());
//    transform.lookAt({0, 0, 0}, {0, -1, -1}, {0, -1, 0});
//    transform.perspective(45, 1, 2, 50);


    // Set modelview-projection matrix
//    program->setUniformValue("MVP", mvp.projection * mvp.view * mvp.model);
//    program->setUniformValue("lightMVP", lightMVP.projection * lightMVP.view * lightMVP.model);
    program->setUniformValue("spotLightMVP", mvp.projection * m_spotLight.getProjection());

    PolyhedronDrawer drawer;
    drawer.init();
//    drawer.setLight(&m_light);
    drawer.setSpotLight(&m_spotLight);
    for (int i = 0; i < m_objects.size(); i++) {
        drawer.setPolyhedron(&(m_objects[i]));
        drawer.update();
        drawer.drawShadow(program);
    }
}
