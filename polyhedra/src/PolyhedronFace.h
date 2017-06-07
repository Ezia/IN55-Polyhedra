#ifndef POLYHEDRONFACE_H
#define POLYHEDRONFACE_H

#include <QVector3D>
#include <QVector>

#include "Colors.h"
#include "Types.h"

class PolyhedronVertex;

class PolyhedronFace
{
public:
    PolyhedronFace(QList<PolyhedronVertex*> vertices, QVector3D color = WHITE);

    PolyhedronFace(QVector3D color = WHITE);

    ~PolyhedronFace();

    QVector3D getNormal();
    QVector3D getColor() const;
    PolyhedronVertex* getVertex(int32 id) const;
    int32 getVertexNbr() const;

    void setColor(QVector3D color);
    void removeAllVertices();
    void removeVertex(int32 id);
    // Vertices storage should be managed by the user
    // Vertices are assumed to be ordered in counter clockwise order and on the same plan
    // The shape should be convex (for rendering purpose)
    void setVertices(QList<PolyhedronVertex*> vertices);
    void addVertices(QList<PolyhedronVertex*> vertices);
    void addVertex(PolyhedronVertex* vertex);

private:
    // computed normal vector from the 3 first vertices
    // vertices are assumed to be on the same plan
    void computeNormal();

    QList<PolyhedronVertex*> m_vertices;

    // face properties
    QVector3D m_color;
    QVector3D m_normal;
    // is set to false if face normal should be re-computed
    bool m_normalComputed;
};


#endif // POLYHEDRONFACE_H
