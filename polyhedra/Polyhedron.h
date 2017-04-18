#ifndef POLYHEDRA_H
#define POLYHEDRA_H

#include <QVector3D>
#include <QPair>
#include <QList>


#include <QList>
#include <QVector3D>
#include <QPair>

// Rules :
// Face vertices are listed in counter clockwise order
// A face is a least composed of 3 vertices
// Vertices sharing the same face must be coplanar
// Colors in RGB

#define DEFAULT_FACE_COLOR QVector3D(0.5, 0.5, 0.5)
#define RED QVector3D(1, 0, 0)
#define GREEN QVector3D(0, 1, 0)
#define BLUE QVector3D(0, 0, 1)
#define PURPLE QVector3D(1, 0, 1)
#define YELLOW QVector3D(1, 1, 0)
#define TURQUOISE QVector3D(0, 1, 1)

class PolyhedronVertex;
class PolyhedronFace;

class PolyhedronVertex {
public:
    PolyhedronVertex(double x, double y, double z);
    PolyhedronVertex(QVector3D position);

    QVector3D position;
};

class PolyhedronFace {
public:
    PolyhedronFace(QVector3D color);

    // counter clockwise
    QList<PolyhedronVertex*> adjVertices;
    QVector3D color;
};

class Polyhedron {
public:
    // init structure
    virtual ~Polyhedron() {}
    virtual void init() {}

    QList<PolyhedronVertex> vertices;
    QList<PolyhedronFace> faces;
};

#endif // POLYHEDRA_H
