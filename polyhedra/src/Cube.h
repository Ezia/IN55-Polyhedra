#ifndef CUBE_H
#define CUBE_H

#include "Polyhedron.h"

#include <QVector3D>

class Cube : public Polyhedron
{
public:
    Cube(QVector3D position = {0, 0, 0}, QVector3D dimension = {1, 1, 1}) :
        Polyhedron(false),
        m_position(position),
        m_dimension(dimension),
        m_upToDate(false)
    {}

    // update the cube structure based on position and dimension fields
    virtual void update();

    QVector3D getPosition() const {return m_position;}
    QVector3D getDimension() const {return m_dimension;}

    void setPosition(QVector3D position) {m_position = position; m_upToDate = false;}
    void setDimension(QVector3D dimension) {m_dimension = dimension; m_upToDate = false;}

private:
     // center of the cube
    QVector3D m_position;
    QVector3D m_dimension;

    bool m_upToDate;
};

#endif // CUBE_H
