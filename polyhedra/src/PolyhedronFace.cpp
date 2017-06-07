#include "PolyhedronFace.h"

#include <assert.h>

#include "PolyhedronVertex.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

PolyhedronFace::PolyhedronFace(QList<PolyhedronVertex *> vertices, QVector3D color) :
    m_vertices(),
    m_color(color),
    m_normal(0, 0, 0),
    m_normalComputed(false)
{
    addVertices(vertices);
}

PolyhedronFace::PolyhedronFace(QVector3D color) :
    m_vertices(),
    m_color(color),
    m_normal(0, 0, 0),
    m_normalComputed(false)
{}

PolyhedronFace::~PolyhedronFace() {
    removeAllVertices();
}

//============================= ATTRIBUTE ACCESSORS ==========================

QVector3D PolyhedronFace::getNormal()
{
    if (!m_normalComputed)
    {
        computeNormal();
    }
    return m_normal;
}

QVector3D PolyhedronFace::getColor() const
{
    return m_color;
}

void PolyhedronFace::setColor(QVector3D color)
{
    m_color = color;
}

PolyhedronVertex *PolyhedronFace::getVertex(int32 id) const
{
    assert(id >= 0 && id < m_vertices.size());
    return m_vertices[id];
}

int32 PolyhedronFace::getVertexNbr() const
{
    return m_vertices.size();
}

void PolyhedronFace::removeAllVertices()
{
    for (int32 i = 0; i < m_vertices.size(); i++)
    {
        removeVertex(i);
    }
}

void PolyhedronFace::removeVertex(int32 id)
{
    assert(id >= 0 && id < m_vertices.size());
    m_vertices.at(id)->removeFace(this);
    m_vertices.removeAt(id);
    m_normalComputed = false;
}

void PolyhedronFace::setVertices(QList<PolyhedronVertex *> vertices)
{
    removeAllVertices(); addVertices(vertices);
}

void PolyhedronFace::addVertices(QList<PolyhedronVertex *> vertices)
{
    for (int32 i = 0; i < vertices.size(); i++)
    {
        addVertex(vertices.at(i));
    }
}

void PolyhedronFace::addVertex(PolyhedronVertex *vertex)
{
    m_vertices.append(vertex);
    vertex->addFace(this);
    m_normalComputed = false;
}

/////////////////////////////// PRIATE    ///////////////////////////////////////

//============================= OPERATIONS ===================================

void PolyhedronFace::computeNormal()
{
    assert(m_vertices.size() >= 3);
    QVector3D v1 = m_vertices[1]->getPosition() - m_vertices[0]->getPosition();
    QVector3D v2 = m_vertices[2]->getPosition() - m_vertices[1]->getPosition();
    m_normal = QVector3D::crossProduct(v1, v2).normalized();
    m_normalComputed = true;
}
