#ifndef POLYHEDRA_H
#define POLYHEDRA_H

#include <QVector3D>
#include <QPair>
#include <QList>

#include <assert.h>
#include <QList>
#include <QVector3D>
#include <QPair>
#include <initializer_list>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "PolyhedronVertex.h"
#include "PolyhedronFace.h"
#include "Colors.h"
#include "Types.h"

// Rules :
// Face vertices are listed in counter clockwise order
// A face is at least composed of 3 vertices
// Vertices sharing the same face must be coplanar
// Colors in RGB

class Polyhedron : public QOpenGLFunctions
{
public:
    Polyhedron(bool smoothNormals, QList<PolyhedronVertex> vertices = {});

    Polyhedron(Polyhedron const& polyhedron);

    Polyhedron &operator=(Polyhedron const& polyhedron);

    virtual ~Polyhedron();

    // update structure based on some internal parameters
    // must be overloaded by inheriting classes
    // this function should not generate overhead when the structure should not be modified
    virtual void updateGeometry();

    // set the same color for every face
    void setGeometryColor(QVector3D color);

    int32 getVertexNbr() const;
    int32 getFaceNbr() const;
    // face vertices should NOT be modified
    PolyhedronFace *getFace(int32 id) const;
    PolyhedronVertex* getVertex(int32 id) const;

    // rendering
    // Assumes the given shader program has been bound
    void drawRender(QOpenGLShaderProgram* program);
    void drawShadow(QOpenGLShaderProgram* program);
    void drawBasic(QOpenGLShaderProgram* program);

    // remove all faces and vertices
    void removeAll();
    void removeAllFaces();
    void removeFace(int32 id);
    // remove faces
    void setVertices(QList<PolyhedronVertex> vertices);
    void addVertex(PolyhedronVertex vertex);
    void addVertices(QList<PolyhedronVertex> vertices);
    void addFace(QList<int32> indices, QVector3D color = WHITE);

private:

    QList<PolyhedronVertex*> m_vertices;
    QList<PolyhedronFace*> m_faces;
    bool m_smoothNormals;

    // vertex buffer objects (VBO)
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    GLsizei m_indexNbr;

    bool m_buffersComputed;

    void updateBuffers();

    // function called
    void updateRendering();
};

#endif // POLYHEDRA_H
