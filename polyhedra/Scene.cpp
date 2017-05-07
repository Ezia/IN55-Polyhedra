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

    Cube cube;
    cube.init();
    m_objects.append(cube);
    m_objects[0].setColor(GREEN);

    Cube cube2;
    cube2.setPosition({0, 0, -1});
    cube2.setDimension({4, 4, 0.2});
    cube2.init();
    m_objects.append(cube2);
    m_objects[1].setColor(BLUE);

    m_light.setPosition({0, 0, 3});
    m_light.init();
}

void Scene::draw(QOpenGLShaderProgram *program, MVPMatrix mvp)
{
    // Set modelview-projection matrix
    program->setUniformValue("mvp_matrix", mvp.projection * mvp.view * mvp.model);
    program->setUniformValue("mv_matrix", mvp.view * mvp.model);
    PolyhedronDrawer drawer;
    drawer.init();
    drawer.setLight(&m_light);
    for (int i = 0; i < m_objects.size(); i++) {
        drawer.setPolyhedron(&(m_objects[i]));
        drawer.update();
        drawer.draw(program);
    }

    m_light.update();
    m_light.draw(program);
}

void Scene::drawShadow(QOpenGLShaderProgram *program, MVPMatrix mvp)
{
    MVPMatrix lightMVP;
    lightMVP.model = mvp.model;
    lightMVP.view.translate(-m_light.getPosition());
    lightMVP.view.lookAt({0, 0, 0}, {0, -1, -1}, {0, -1, 0});
    lightMVP.projection.perspective(45, 1, 2, 50);
//    lightMVP.projection = mvp.projection;

    // Set modelview-projection matrix
    program->setUniformValue("MVP", mvp.projection * mvp.view * mvp.model);
    program->setUniformValue("lightMVP", lightMVP.projection * lightMVP.view * lightMVP.model);

    PolyhedronDrawer drawer;
    drawer.init();
    drawer.setLight(&m_light);
    for (int i = 0; i < m_objects.size(); i++) {
        drawer.setPolyhedron(&(m_objects[i]));
        drawer.update();
        drawer.drawShadow(program);
    }
}
