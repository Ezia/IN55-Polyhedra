#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QMatrix4x4>
#include <QVector3D>

#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

// Spot light based on a projective matrix
class SpotLight
{
public:
    SpotLight() :
        m_direction(0, 0, -1),
        m_upDirection(0, 1, 0),
        m_position(0, 0, 0),
        m_verticalAngle(45),
        m_horizontalAngle(45),
        m_nearPlan(2),
        m_farPlan(50),
        m_pixelPerDegree(20),
        m_shadowTextureBias(0.005),
        m_shadowTexture(NULL),
        m_projectionUpToDate(false),
        m_shadowTextureUpToDate(false),
        m_specular(1, 1, 1),
        m_diffuse(0.8, 0.8, 0.8),
        m_ambiant(0.1, 0.1, 0.1)
    {}

    virtual ~SpotLight() {if (m_shadowTexture) delete m_shadowTexture;}

    QVector3D getSpecular() const {return m_specular;}
    QVector3D getDiffuse() const {return m_diffuse;}
    QVector3D getAmbiant() const {return m_ambiant;}
    QVector3D getDirection() const {return m_direction;}
    QVector3D getPosition() const {return m_position;}
    QVector3D getUpDirection() const {return m_upDirection;}
    float getVerticalAngle() const {return m_verticalAngle;}
    float getHorizontalAngle() const {return m_horizontalAngle;}
    float getNearPlan() const {return m_nearPlan;}
    float getFarPlan() const {return m_farPlan;}
    float getPixelPerDegree() const {return m_pixelPerDegree;}
    float getShadowTextureBias() const {return m_shadowTextureBias;}
    QMatrix4x4 getProjection() {updateProjection(); return m_projection;}
    QOpenGLFramebufferObject* getShadowTexture() {updateShadowTexture(); return m_shadowTexture;}

    void setSpecular(QVector3D specular) {m_specular = specular;}
    void setAmbiant(QVector3D ambiant) {m_ambiant = ambiant;}
    void setDiffuse(QVector3D diffuse) {m_diffuse = diffuse;}
    void setDirection(QVector3D direction) {m_direction = direction; m_projectionUpToDate = false;}
    void setUpDirection(QVector3D upDirection) {m_upDirection = upDirection; m_projectionUpToDate = false;}
    void setPosition(QVector3D position) {m_position = position; m_projectionUpToDate = false;}
    void setNearPlan(float nearPlan) {m_nearPlan = nearPlan; m_projectionUpToDate = false;}
    void setFarPlan(float farPlan) {m_farPlan = farPlan; m_projectionUpToDate = false;}
    void setVerticalAngle(float verticalAngle) {m_verticalAngle = verticalAngle; m_projectionUpToDate = false;  m_shadowTextureUpToDate = false;}
    void setHorizontalAngle(float horizontalAngle) {m_horizontalAngle = horizontalAngle; m_projectionUpToDate = false;  m_shadowTextureUpToDate = false;}
    void setPixelPerDegree(float pixelPerDegree) {m_pixelPerDegree = pixelPerDegree; m_shadowTextureUpToDate = false;}
    void setShadowTextureBias(float shadowTextureBias) {m_shadowTextureBias = shadowTextureBias;}

private:
    void updateShadowTexture();
    void updateProjection();

    // transform from world ref to projected light ref
    QMatrix4x4 m_projection;
    QVector3D m_direction, m_upDirection, m_position;
    float m_verticalAngle, m_horizontalAngle, m_nearPlan, m_farPlan, m_pixelPerDegree, m_shadowTextureBias;

    QOpenGLFramebufferObject* m_shadowTexture;

    bool m_projectionUpToDate, m_shadowTextureUpToDate;

    QVector3D m_specular, m_diffuse, m_ambiant;
};

#endif // SPOTLIGHT_H
