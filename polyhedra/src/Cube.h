#ifndef CUBE_H
#define CUBE_H

#include <QVector3D>

#include "Polyhedron.h"

class Cube : public Polyhedron
{
public:
    Cube(QVector3D position = {0, 0, 0}, QVector3D dimension = {1, 1, 1});

    // update the cube structure based on position and dimension fields
    virtual void updateGeometry();

    QVector3D getPosition() const;
    QVector3D getDimension() const;

    void setPosition(QVector3D position);
    void setDimension(QVector3D dimension);

private:
     // center of the cube
    QVector3D m_position;
    QVector3D m_dimension;

    bool m_upToDate;
};

#endif // CUBE_H
