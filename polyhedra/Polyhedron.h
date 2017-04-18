#ifndef POLYHEDRA_H
#define POLYHEDRA_H

#include <QVector3D>
#include <QPair>
#include <QList>


#include <QList>
#include <QVector3D>
#include <QPair>
#include <initializer_list>

// Rules :
// Face vertices are listed in counter clockwise order
// A face is a least composed of 3 vertices
// Vertices sharing the same face must be coplanar
// Colors in RGB

#define DEFAULT_FACE_COLOR QVector3D(1, 1, 1)
#define RED QVector3D(1, 0, 0)
#define GREEN QVector3D(0, 1, 0)
#define BLUE QVector3D(0, 0, 1)
#define PURPLE QVector3D(1, 0, 1)
#define YELLOW QVector3D(1, 1, 0)
#define TURQUOISE QVector3D(0, 1, 1)

class PolyhedronVertex {
public:
    PolyhedronVertex(double x, double y, double z);
    PolyhedronVertex(QVector3D position);

    QVector3D getPosition();

private:
    QVector3D m_position;
};

class PolyhedronFace {
public:
    PolyhedronFace(QVector3D color);

    QVector3D getColor();
    void setColor(QVector3D color);

    void addAdjVertex(PolyhedronVertex* adjVertex);
    void addAdjVertices(QList<PolyhedronVertex*> adjVertex);
    PolyhedronVertex* getAdjVertex(int id);
    int getAdjVertexNbr();
    void clearAdjVertices();

private:
    // counter clockwise order
    QList<PolyhedronVertex*> m_adjVertices;
    QVector3D m_color;
};

class Polyhedron {
public:
    // init structure
    virtual ~Polyhedron() {}
    virtual void init() {}

    void addVertex(PolyhedronVertex vertex);
    void addVertices(QList<PolyhedronVertex> vertices);
    void addFace(PolyhedronFace face);
    void addFaces(QList<PolyhedronFace> faces);
    int getVertexNbr();
    int getFaceNbr();
    PolyhedronFace getFace(int id);
    PolyhedronVertex getVertex(int id);
    void clear();

protected:
    QList<PolyhedronVertex> m_vertices;
    QList<PolyhedronFace> m_faces;
};

#endif // POLYHEDRA_H
