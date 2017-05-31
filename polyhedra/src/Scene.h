#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QOpenGLShaderProgram>
#include "MVPMatrix.h"

#include "SpotLight.h"

class Scene : public QOpenGLFunctions
{
public:
    Scene() :
        m_objects(),
        m_spotLight(),
        m_shadowTextureComputed(false),
        m_viewMatrix(),
        m_projectionMatrix(),
        m_viewPortPosition(),
        m_viewPortDimension()
    {
    }

    ~Scene() {for (int i = 0; i < m_objects.size(); i++) delete m_objects[i];}

    // Scene building
    // Objects and light are hard coded here for easy testing
    void init();

    // draw the scene objects
    void drawRender();

    // draw a shadow map from the spot light point of view
    void drawShadow();

    void drawBasic();

    QMatrix4x4 getViewMatrix() const {return m_viewMatrix;}
    QMatrix4x4 getProjectionMatrix() const {return m_viewMatrix;}
    QVector2D getViewPortDimension() const {return m_viewPortDimension;}
    QVector2D getViewPortPosition() const {return m_viewPortPosition;}

    void setViewMatrix(QMatrix4x4 viewMatrix) {m_viewMatrix = viewMatrix;}
    void setProjectionMatrix(QMatrix4x4 projectionMatrix) {m_projectionMatrix = projectionMatrix;}
    void setViewPortPosition(QVector2D viewPortPosition) {m_viewPortPosition = viewPortPosition;}
    void setViewPortDImension(QVector2D viewPortDimension) {m_viewPortDimension = viewPortDimension;}

private:

    // objects in the scene
    QList<Polyhedron*> m_objects;

    // spot light of the scene
    SpotLight m_spotLight;
    bool m_shadowTextureComputed;

    QMatrix4x4 m_viewMatrix, m_projectionMatrix;
    QVector2D m_viewPortPosition, m_viewPortDimension;

    QOpenGLShaderProgram m_renderProgram, m_shadowProgram, m_basicProgram;
};

#endif // SCENE_H
