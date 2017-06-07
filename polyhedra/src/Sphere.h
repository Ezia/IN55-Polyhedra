#ifndef SPHERE_H
#define SPHERE_H

#include "Polyhedron.h"
#include "Types.h"

#include <QVector3D>

class Sphere : public Polyhedron
{
public:
    Sphere(QVector3D position = {0., 0., 0.}, float32 radius = 1., int32 xyResolution = 20, int32 xzResolution = 10);

    // update the cube structure based on position and dimension fields
    virtual void updateGeometry();

    QVector3D getPosition() const;
    float32 getRadius() const;
    int32 getXYResolution() const;
    int32 getXZResolution() const;

    void setPosition(QVector3D position);
    void setRadius(float32 radius);
    void setXYResolution(int32 xyResolution);
    void setXZResolution(int32 xzResolution);

private:
    // center of the sphere
    QVector3D m_position;

    // radius of the sphere
    float32 m_radius;

    // resolution of the sphere, on the XY plan
    int32 m_xyResolution;

    // resolution of the sphere, on the XZ plan
    int32 m_xzResolution;

    bool m_upToDate;
};

#endif // SPHERE_H
