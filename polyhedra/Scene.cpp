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
    cube2.setPosition({1.1, 0, 0});
    cube2.init();
    m_objects.append(cube2);
    m_objects[1].setColor(BLUE);

    m_light.setPosition({1, 0.6, 1});
    m_light.init();
}

void Scene::draw(QGLShaderProgram *program)
{
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
