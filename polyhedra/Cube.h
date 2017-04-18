#ifndef CUBE_H
#define CUBE_H

#include "Polyhedron.h"

#include <QVector3D>

class Cube : public Polyhedron
{
public:
    Cube();

    void init();

    void setPosition(double x, double y, double z);
    void setPosition(QVector3D position);
    void setDimension(double xLength, double yLength, double zLength);
    void setDimension(QVector3D dimension);

private:
    QVector3D m_position; // center of the cube
    QVector3D m_dimension;
};

#endif // CUBE_H
