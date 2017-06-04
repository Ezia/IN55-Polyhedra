#ifndef SPHERE_H
#define SPHERE_H

#include "Polyhedron.h"

#include <QVector3D>

class Sphere : public Polyhedron
{
public:
    Sphere(QVector3D position = {0., 0., 0.}, float radius = 1., int xyResolution = 20, int xzResolution = 10) :
        m_position(position),
        m_radius(radius),
        m_xyResolution(xyResolution),
        m_xzResolution(xzResolution),
        m_upToDate(false)
    {}

    // update the cube structure based on position and dimension fields
    virtual void update();

    QVector3D getPosition() const {return m_position;}
    float getRadius() const {return m_radius;}
    int getXYResolution() const {return m_xyResolution;}
    int getXZResolution() const {return m_xzResolution;}

    void setPosition(QVector3D position) {m_position = position ; m_upToDate = false;}
    void setRadius(float radius) {m_radius = radius ; m_upToDate = false;}
    void setXYResolution(int xyResolution) {m_xyResolution = xyResolution; m_upToDate = false;}
    void setXZResolution(int xzResolution) {m_xzResolution = xzResolution; m_upToDate = false;}

private:
    // center of the sphere
    QVector3D m_position;

    // radius of the sphere
    float m_radius;

    // resolution of the sphere, on the XY plan
    int m_xyResolution;

    // resolution of the sphere, on the XZ plan
    int m_xzResolution;

    bool m_upToDate;
};

#endif // SPHERE_H
