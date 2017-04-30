#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

class Light
{
public:
    Light();

    void setPosition(QVector3D position);
    void setDiffuse(QVector3D diffuse);
    void setAmbiant(QVector3D ambiant);

private:
    QVector3D m_position, m_diffuse, m_ambiant;
};

#endif // LIGHT_H
