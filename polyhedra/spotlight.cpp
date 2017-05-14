#include "spotlight.h"


SpotLight::SpotLight() :
    m_direction(0, 0, -1),
    m_upDirection(0, 1, 0),
    m_position(0, 0, 0),
    m_verticalAngle(45),
    m_horizontalAngle(45),
    m_nearPlan(2),
    m_farPlan(50)
{}

void SpotLight::update()
{
    m_projection.setToIdentity();
    m_projection.translate(-m_position);
    m_projection.lookAt(/*m_position*/ {0, 0, 0}, /*m_position+*/m_direction, m_upDirection);
//    m_projection.perspective(m_verticalAngle, m_horizontalAngle/m_verticalAngle, m_nearPlan, m_farPlan);
}
