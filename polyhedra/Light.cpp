#include "Light.h"

Light::Light() :
    m_position(0, 0, 0),
    m_diffuse(0.8, 0.8, 0.8),
    m_ambiant(0.1, 0.1, 0.1)
{
}

void Light::setPosition(QVector3D position)
{
    m_position = position;
}

void Light::setDiffuse(QVector3D diffuse)
{
    m_diffuse = diffuse;
}

void Light::setAmbiant(QVector3D ambiant)
{
    m_ambiant = ambiant;
}
