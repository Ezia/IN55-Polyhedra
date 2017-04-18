#include "Polyhedron.h"

#include <assert.h>

PolyhedronVertex::PolyhedronVertex(double x, double y, double z) :
    m_position(QVector3D(x, y, z))
{}

PolyhedronVertex::PolyhedronVertex(QVector3D position) :
    m_position(position)
{}

QVector3D PolyhedronVertex::getPosition() {
    return m_position;
}


PolyhedronFace::PolyhedronFace(QVector3D color) :
    m_color(color)
{}

QVector3D PolyhedronFace::getColor() {
    return m_color;
}

void PolyhedronFace::setColor(QVector3D color)
{
    this->m_color = color;
}

void PolyhedronFace::addAdjVertex(PolyhedronVertex* adjVertex)
{
    assert(adjVertex != NULL);
    m_adjVertices.push_back(adjVertex);
}

void PolyhedronFace::addAdjVertices(QList<PolyhedronVertex *> adjVertex) {
    m_adjVertices.append(adjVertex);
}

PolyhedronVertex* PolyhedronFace::getAdjVertex(int id)
{
    assert(id >= 0 && id < m_adjVertices.size());
    return m_adjVertices[id];
}

int PolyhedronFace::getAdjVertexNbr()
{
    return m_adjVertices.size();
}

void PolyhedronFace::clearAdjVertices()
{
    m_adjVertices.clear();
}


void Polyhedron::addVertex(PolyhedronVertex vertex)
{
    m_vertices.push_back(vertex);
}

void Polyhedron::addVertices(QList<PolyhedronVertex> vertices)
{
    this->m_vertices.append(vertices);
}

void Polyhedron::addFace(PolyhedronFace face)
{
    m_faces.append(face);
}

void Polyhedron::addFaces(QList<PolyhedronFace> faces)
{
    this->m_faces.append(faces);
}

int Polyhedron::getVertexNbr()
{
    return m_vertices.size();
}

int Polyhedron::getFaceNbr()
{
    return m_faces.size();
}

PolyhedronFace Polyhedron::getFace(int id)
{
    assert(id >= 0 && id < m_faces.size());
    return m_faces[id];
}

PolyhedronVertex Polyhedron::getVertex(int id)
{
    assert(id >= 0 && id < m_vertices.size());
    return m_vertices[id];
}

void Polyhedron::clear()
{
    m_vertices.clear();
    m_faces.clear();
}
