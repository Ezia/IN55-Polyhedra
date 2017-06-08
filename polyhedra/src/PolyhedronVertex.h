#ifndef POLYHEDRONVERTEX_H
#define POLYHEDRONVERTEX_H

#include <QVector3D>
#include <QVector>

#include "Types.h"

class PolyhedronFace;

class PolyhedronVertex
{
public:
    PolyhedronVertex(QVector3D position = {0, 0, 0});
    PolyhedronVertex(const PolyhedronVertex& vertex);

    QVector3D getPosition() const;
    void setPosition(QVector3D position);

    void clearFaces();
    void removeFace(PolyhedronFace* face);
    PolyhedronFace* getFace(int32 i);
    void addFace(PolyhedronFace* face);
    void addFaces(QVector<PolyhedronFace*> faces);
    int32 getFaceNbr();

    QVector3D getNormal();

private:
    void computeNormal();

    QVector3D m_position;
    QVector<PolyhedronFace*> m_faces;
    QVector3D m_normal;
    bool m_normalComputed;
};


#endif // POLYHEDRONVERTEX_H
