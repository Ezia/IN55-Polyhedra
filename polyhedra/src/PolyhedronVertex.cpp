#include "PolyhedronVertex.h"

#include <assert.h>

#include "PolyhedronFace.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

PolyhedronVertex::PolyhedronVertex(QVector3D position) :
    m_position(position),
    m_faces(),
    m_normal(0, 0, 0),
    m_normalComputed(false)
{}

PolyhedronVertex::PolyhedronVertex(const PolyhedronVertex &vertex) :
    m_position(vertex.m_position),
    m_faces(),
    m_normal(0, 0, 0),
    m_normalComputed(false)
{}

//============================= ATTRIBUTE ACCESSORS ==========================

QVector3D PolyhedronVertex::getPosition() const
{
    return m_position;
}

void PolyhedronVertex::setPosition(QVector3D position)
{
    m_position = position;
}

void PolyhedronVertex::clearFaces()
{
    m_faces.clear();
    m_normalComputed = false;
}

void PolyhedronVertex::removeFace(PolyhedronFace *face)
{
    m_faces.removeOne(face);
    m_normalComputed = false;
}

PolyhedronFace *PolyhedronVertex::getFace(int32 i)
{
    assert(i >= 0 && i < m_faces.size());
    return m_faces.at(i);
}

void PolyhedronVertex::addFace(PolyhedronFace *face)
{
    m_faces.append(face);
    m_normalComputed = false;
}

void PolyhedronVertex::addFaces(QVector<PolyhedronFace *> faces)
{
    for (int32 i = 0; i < faces.size(); i++)
    {
        addFace(faces.at(i));
    }
}

int32 PolyhedronVertex::getFaceNbr()
{
    return m_faces.size();
}

QVector3D PolyhedronVertex::getNormal()
{
    if(!m_normalComputed)
    {
        computeNormal();
    }
    return m_normal;
}

/////////////////////////////// PRIATE    ///////////////////////////////////////

//============================= OPERATIONS ===================================




void PolyhedronVertex::computeNormal()
{
    assert(m_faces.size() > 0);
    m_normal[0] = 0;
    m_normal[1] = 0;
    m_normal[2] = 0;
    for (int32 i = 0; i < m_faces.size(); i++)
    {
        m_normal += m_faces.at(i)->getNormal();
    }
    m_normal.normalize();
    m_normalComputed = true;
}
