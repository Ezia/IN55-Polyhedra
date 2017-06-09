#include "SpotLight.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SpotLight::SpotLight() :
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
    m_shadowTextureUpToDate(false),
    m_specular(1, 1, 1),
    m_diffuse(0.8, 0.8, 0.8),
    m_ambient(0.1, 0.1, 0.1)
{}

SpotLight::~SpotLight()
{
    if (m_shadowTexture)
    {
        delete m_shadowTexture;
    }
}

//============================= ATTRIBUTE ACCESSORS ==========================

QVector3D SpotLight::getSpecular() const
{
    return m_specular;
}

QVector3D SpotLight::getDiffuse() const
{
    return m_diffuse;
}

QVector3D SpotLight::getAmbient() const
{
    return m_ambient;
}

QVector3D SpotLight::getDirection() const
{
    return m_direction;
}

QVector3D SpotLight::getPosition() const
{
    return m_position;
}

QVector3D SpotLight::getUpDirection() const
{
    return m_upDirection;
}

float32 SpotLight::getVerticalAngle() const
{
    return m_verticalAngle;
}

float32 SpotLight::getHorizontalAngle() const
{
    return m_horizontalAngle;
}

float32 SpotLight::getNearPlan() const
{
    return m_nearPlan;
}

float32 SpotLight::getFarPlan() const
{
    return m_farPlan;
}

float32 SpotLight::getPixelPerDegree() const
{
    return m_pixelPerDegree;
}

float32 SpotLight::getShadowTextureBias() const
{
    return m_shadowTextureBias;
}

QMatrix4x4 SpotLight::getProjection()
{
    m_projection.setToIdentity();
    m_projection.perspective(m_verticalAngle, m_horizontalAngle/m_verticalAngle, m_nearPlan, m_farPlan);
    m_projection.lookAt(m_position, m_position+m_direction, m_upDirection);
    return m_projection;
}

QOpenGLFramebufferObject *SpotLight::getShadowTexture()
{
    updateShadowTexture();
    return m_shadowTexture;
}

void SpotLight::setSpecular(QVector3D specular)
{
    m_specular = specular;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setAmbient(QVector3D ambient)
{
    m_ambient = ambient;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setDiffuse(QVector3D diffuse)
{
    m_diffuse = diffuse;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setDirection(QVector3D direction)
{
    m_direction = direction;
}

void SpotLight::setUpDirection(QVector3D upDirection)
{
    m_upDirection = upDirection;
}

void SpotLight::setPosition(QVector3D position)
{
    m_position = position;
}

void SpotLight::setNearPlan(float32 nearPlan)
{
    m_nearPlan = nearPlan;
}

void SpotLight::setFarPlan(float32 farPlan)
{
    m_farPlan = farPlan;
}

void SpotLight::setVerticalAngle(float32 verticalAngle)
{
    m_verticalAngle = verticalAngle;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setHorizontalAngle(float32 horizontalAngle)
{
    m_horizontalAngle = horizontalAngle;
//    m_projectionUpToDate = false;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setPixelPerDegree(float32 pixelPerDegree)
{
    m_pixelPerDegree = pixelPerDegree;
    m_shadowTextureUpToDate = false;
}

void SpotLight::setShadowTextureBias(float32 shadowTextureBias)
{
    m_shadowTextureBias = shadowTextureBias;
    m_shadowTextureUpToDate = false;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////////

//============================= OPERATIONS ===================================

void SpotLight::updateShadowTexture()
{
    if (!m_shadowTextureUpToDate)
    {
        if (m_shadowTexture)
        {
            delete m_shadowTexture;
        }
        m_shadowTexture = new QOpenGLFramebufferObject(m_pixelPerDegree*m_horizontalAngle, m_pixelPerDegree*m_verticalAngle, QOpenGLFramebufferObject::Depth);
        m_shadowTextureUpToDate = true;
    }

}

