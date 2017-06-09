#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QMatrix4x4>
#include <QVector3D>

#include "Types.h"

class QOpenGLFramebufferObject;
class QOpenGLShaderProgram;

// Spot light based on a projective matrix
class SpotLight
{
public:
    SpotLight();

    virtual ~SpotLight();

    QVector3D getSpecular() const;
    QVector3D getDiffuse() const;
    QVector3D getAmbient() const;
    QVector3D getDirection() const;
    QVector3D getPosition() const;
    QVector3D getUpDirection() const;
    float32 getVerticalAngle() const;
    float32 getHorizontalAngle() const;
    float32 getNearPlan() const;
    float32 getFarPlan() const;
    float32 getPixelPerDegree() const;
    float32 getShadowTextureBias() const;
    QMatrix4x4 getProjection();
    QOpenGLFramebufferObject* getShadowTexture();

    void setSpecular(QVector3D specular);
    void setAmbient(QVector3D ambient);
    void setDiffuse(QVector3D diffuse);
    void setDirection(QVector3D direction);
    void setUpDirection(QVector3D upDirection);
    void setPosition(QVector3D position);
    void setNearPlan(float32 nearPlan);
    void setFarPlan(float32 farPlan);
    void setVerticalAngle(float32 verticalAngle);
    void setHorizontalAngle(float32 horizontalAngle);
    void setPixelPerDegree(float32 pixelPerDegree);
    void setShadowTextureBias(float32 shadowTextureBias);

private:
    void updateShadowTexture();

    // transform from world ref to projected light ref
    QMatrix4x4 m_projection;
    QVector3D m_direction;
    QVector3D m_upDirection;
    QVector3D m_position;
    float32 m_verticalAngle;
    float32 m_horizontalAngle;
    float32 m_nearPlan;
    float32 m_farPlan;
    float32 m_pixelPerDegree;
    float32 m_shadowTextureBias;

    QOpenGLFramebufferObject* m_shadowTexture;

    bool m_shadowTextureUpToDate;

    QVector3D m_specular;
    QVector3D m_diffuse;
    QVector3D m_ambient;
};

#endif // SPOTLIGHT_H
