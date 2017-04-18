#include "Cube.h"

Cube::Cube() :
    m_dimension(1, 1, 1)
{}

void Cube::init()
{
    clear();

    m_vertices.push_back(PolyhedronVertex(m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2));

    m_vertices.push_back(PolyhedronVertex(m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2));
    m_vertices.push_back(PolyhedronVertex(m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2));

    m_faces.push_back(PolyhedronFace(RED));
    m_faces.push_back(PolyhedronFace(GREEN));
    m_faces.push_back(PolyhedronFace(BLUE));
    m_faces.push_back(PolyhedronFace(PURPLE));
    m_faces.push_back(PolyhedronFace(YELLOW));
    m_faces.push_back(PolyhedronFace(TURQUOISE));

    m_faces[0].addAdjVertices({&m_vertices[0], &m_vertices[1], &m_vertices[2], &m_vertices[3]});
    m_faces[1].addAdjVertices({&m_vertices[2], &m_vertices[6], &m_vertices[7], &m_vertices[3]});
    m_faces[2].addAdjVertices({&m_vertices[1], &m_vertices[5], &m_vertices[6], &m_vertices[2]});
    m_faces[3].addAdjVertices({&m_vertices[7], &m_vertices[4], &m_vertices[0], &m_vertices[3]});
    m_faces[4].addAdjVertices({&m_vertices[4], &m_vertices[5], &m_vertices[1], &m_vertices[0]});
    m_faces[5].addAdjVertices({&m_vertices[5], &m_vertices[4], &m_vertices[7], &m_vertices[6]});
}

void Cube::setPosition(double x, double y, double z)
{
    m_position = {x, y, z};
}

void Cube::setPosition(QVector3D position)
{
    m_position = position;
}

void Cube::setDimension(double xLength, double yLength, double zLength)
{
    m_dimension = {xLength, yLength, zLength};
}

void Cube::setDimension(QVector3D dimension)
{
    m_dimension = dimension;
}
