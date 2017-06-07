#include "Cube.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Cube::Cube(QVector3D position, QVector3D dimension) :
    Polyhedron(false),
    m_position(position),
    m_dimension(dimension),
    m_upToDate(false)
{}

//============================= ATTRIBUTE ACCESSORS ==========================

QVector3D Cube::getPosition() const
{
    return m_position;
}

QVector3D Cube::getDimension() const
{
    return m_dimension;
}

void Cube::setPosition(QVector3D position)
{
    m_position = position; m_upToDate = false;
}

void Cube::setDimension(QVector3D dimension)
{
    m_dimension = dimension; m_upToDate = false;
}

//============================= OPERATIONS ===================================

void Cube::updateGeometry()
{
    if (!m_upToDate)
    {
        removeAll();

        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));

        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));

        addFace({0, 1, 2, 3});
        addFace({2, 6, 7, 3});
        addFace({1, 5, 6, 2});
        addFace({7, 4, 0, 3});
        addFace({4, 5, 1, 0});
        addFace({5, 4, 7, 6});

        m_upToDate = true;
    }
}
