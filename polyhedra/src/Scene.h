#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <Polyhedron.h>
#include <QOpenGLShaderProgram>

#include "SpotLight.h"
#include "Types.h"
#include "FaceShrinkingFilter.h"

class Scene : public QOpenGLFunctions
{
public:
    Scene();

    ~Scene();

    // Scene building
    // Objects and light are hard coded here for easy testing
    void init();

    // draw the scene objects
    void drawRender();

    // draw a shadow map from the spot light point of view
    void drawShadow();

    void drawBasic();

    QMatrix4x4 getViewMatrix() const;
    QMatrix4x4 getProjectionMatrix() const;
    QVector2D getViewPortDimension() const;
    QVector2D getViewPortPosition() const;

    QList<Polyhedron*> getObjectList() const;
    QList<FaceShrinkingFilter*> getFilterList() const;
    SpotLight* getSpotLight();

    void setViewMatrix(QMatrix4x4 viewMatrix);
    void setProjectionMatrix(QMatrix4x4 projectionMatrix);
    void setViewPortPosition(QVector2D viewPortPosition);
    void setViewPortDImension(QVector2D viewPortDimension);
    void notifyShadowMapNeedsComputation();

private:

    // objects in the scene
    QList<Polyhedron*> m_objects;

    // filters in the scene
    QList<FaceShrinkingFilter*> m_filters;

    // spot light of the scene
    SpotLight m_spotLight;
    bool m_shadowTextureComputed;

    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
    QVector2D m_viewPortPosition;
    QVector2D m_viewPortDimension;

    QOpenGLShaderProgram m_renderProgram;
    QOpenGLShaderProgram m_shadowProgram;
    QOpenGLShaderProgram m_basicProgram;
};

#endif // SCENE_H
