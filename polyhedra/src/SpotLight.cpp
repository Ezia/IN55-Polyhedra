#include "SpotLight.h"

void SpotLight::updateShadowTexture()
{
    if (!m_shadowTextureUpToDate) {
        if (m_shadowTexture) delete m_shadowTexture;
        m_shadowTexture = new QOpenGLFramebufferObject(m_pixelPerDegree*m_horizontalAngle, m_pixelPerDegree*m_verticalAngle, QOpenGLFramebufferObject::Depth);
        m_shadowTextureUpToDate = true;
    }

}

void SpotLight::updateProjection()
{
    if (!m_projectionUpToDate) {
        m_projection.setToIdentity();
        m_projection.perspective(m_verticalAngle, m_horizontalAngle/m_verticalAngle, m_nearPlan, m_farPlan);
        m_projection.lookAt(m_position, m_position+m_direction, m_upDirection);
        m_projectionUpToDate = true;
    }
}
