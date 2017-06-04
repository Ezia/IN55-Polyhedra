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

// Rules :
// Face vertices are listed in counter clockwise order
// A face is at least composed of 3 vertices
// Vertices sharing the same face must be coplanar
// Colors in RGB

// *********************************************************************
// Color presets
// *********************************************************************
#define RED QVector3D(1, 0, 0)
#define GREEN QVector3D(0, 1, 0)
#define BLUE QVector3D(0, 0, 1)
#define PURPLE QVector3D(1, 0, 1)
#define YELLOW QVector3D(1, 1, 0)
#define TURQUOISE QVector3D(0, 1, 1)
#define WHITE QVector3D(1, 1, 1)
#define BLACK QVector3D(0, 0, 0)
#define LIGHT_GRAY QVector3D(0.8, 0.8, 0.8)
#define DARK_GRAY QVector3D(0.2, 0.2, 0.2)


// *********************************************************************
// Vertex
// *********************************************************************
class PolyhedronFace;
class PolyhedronVertex {
public:
    PolyhedronVertex(QVector3D position = {0, 0, 0}) :
        m_position(position),
        m_faces(),
        m_normal(0, 0, 0),
        m_normalComputed(false)
    {}

//    PolyhedronVertex(PolyhedronVertex const& vertex) :
//        m_position(vertex.m_position),
//        m_faces(),
//        m_normal(0, 0, 0),
//        m_normalComputed(false)
//    {}

    QVector3D getPosition() const {return m_position;}
    void setPosition(QVector3D position) {m_position = position;}

    void clearFaces() {m_faces.clear(); m_normalComputed = false;}
    void removeFace(PolyhedronFace* face) {m_faces.removeOne(face); m_normalComputed = false;}
    PolyhedronFace* getFace(int i) {assert(i >= 0 && i < m_faces.size()); return m_faces.at(i);}
    void addFace(PolyhedronFace* face) {m_faces.append(face); m_normalComputed = false;}
    void addFaces(QVector<PolyhedronFace*> face) {m_faces.append(face); m_normalComputed = false;}
    int getFaceNbr() {return m_faces.size();}

    QVector3D getNormal() {if(!m_normalComputed) computeNormal(); return m_normal; }

private:
    void computeNormal();

    QVector3D m_position;
    QVector<PolyhedronFace*> m_faces;
    QVector3D m_normal;
    bool m_normalComputed;
};


// *********************************************************************
// Face
// *********************************************************************
class PolyhedronFace {
public:
    PolyhedronFace(QList<PolyhedronVertex*> vertices, QVector3D color = WHITE) :
        m_vertices(),
        m_color(color),
        m_normal(0, 0, 0),
        m_normalComputed(false)
    {
        addVertices(vertices);
    }

    PolyhedronFace(QVector3D color = WHITE) :
        m_vertices(),
        m_color(color),
        m_normal(0, 0, 0),
        m_normalComputed(false)
    {}

//    PolyhedronFace(PolyhedronFace const& face) :
//        m_vertices(),
//        m_color(face.m_color),
//        m_normal(face.m_normal),
//        m_normalComputed(face.m_normalComputed)
//    {
//        addVertices(face.m_vertices);
//    }

    ~PolyhedronFace() {
        removeAllVertices();
    }

    QVector3D getNormal() {if (!m_normalComputed) computeNormal(); return m_normal;}
    QVector3D getColor() const {return m_color;}
    PolyhedronVertex* getVertex(int id) const {assert(id >= 0 && id < m_vertices.size()); return m_vertices[id];}
    int getVertexNbr() const {return m_vertices.size();}

    void setColor(QVector3D color) {m_color = color;}
    void removeAllVertices() {for (int i = 0; i < m_vertices.size(); i++) m_vertices.at(i)->removeFace(this); m_vertices.clear(); m_normalComputed = false;}
    void removeVertex(int id) {assert(id >= 0 && id < m_vertices.size()); m_vertices.at(id)->removeFace(this); m_vertices.removeAt(id); m_normalComputed = false;}
    // Vertices storage should be managed by the user
    // Vertices are assumed to be ordered in counter clockwise order and on the same plan
    // The shape should be convex (for rendering purpose)
    void setVertices(QList<PolyhedronVertex*> vertices) {removeAllVertices(); addVertices(vertices); m_normalComputed = false;}
    void addVertices(QList<PolyhedronVertex*> vertices) {for (int i = 0; i < vertices.size(); i++) addVertex(vertices.at(i)); m_normalComputed = false;}
    void addVertex(PolyhedronVertex* vertex) {m_vertices.append(vertex); vertex->addFace(this); m_normalComputed = false;}

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


// *********************************************************************
// Polyhedron
// *********************************************************************
class Polyhedron : public QOpenGLFunctions {
public:
    Polyhedron(bool smoothNormals, QList<PolyhedronVertex> vertices = {}) :
        m_vertices(),
        m_faces(),
        m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
        m_indexBuffer(QOpenGLBuffer::IndexBuffer),
        m_indexNbr(0),
        m_buffersComputed(false),
        m_smoothNormals(smoothNormals)
    {
        setVertices(vertices);
    }

    Polyhedron(Polyhedron const& polyhedron);

    Polyhedron &operator=(Polyhedron const& polyhedron);

    virtual ~Polyhedron() {removeAll();}

    // update structure based on some internal parameters
    // must be overloaded by inheriting classes
    // this function should not generate overhead when the structure should not be modified
    virtual void update() {}

    // set the same color for every face
    void setColor(QVector3D color) {update(); for (int i = 0; i < m_faces.size(); i++) m_faces[i]->setColor(color); m_buffersComputed = false;}

    int getVertexNbr() const {return m_vertices.size();}
    int getFaceNbr() const {return m_faces.size();}
    // face vertices should NOT be modified
    PolyhedronFace* getFace(int id) const {assert(id >= 0 && id < m_faces.size()); return m_faces[id];}
    PolyhedronVertex* getVertex(int id) const {assert(id >= 0 && id < m_vertices.size()); return m_vertices[id];}

    // rendering
    // Assumes the given shader program has been bound
    void drawRender(QOpenGLShaderProgram* program);
    void drawShadow(QOpenGLShaderProgram* program);
    void drawBasic(QOpenGLShaderProgram* program);

    // remove all faces and vertices
    void removeAll() {deleteFaces(); deleteVertices(); m_buffersComputed = false;}
    void removeAllFaces() {deleteFaces(); m_buffersComputed = false;}
    void removeFace(int id) {assert(id >= 0 && id < m_faces.size()); m_faces.removeAt(id); m_buffersComputed = false;}
    // remove faces
    void setVertices(QList<PolyhedronVertex> vertices) {removeAll(); addVertices(vertices); m_buffersComputed = false;}
    void addVertex(PolyhedronVertex vertex) {m_vertices.push_back(new PolyhedronVertex(vertex)); m_buffersComputed = false;}
    void addVertices(QList<PolyhedronVertex> vertices) {for (int i = 0; i < vertices.size(); i++) addVertex(vertices[i]); m_buffersComputed = false;}
    void addFace(QList<int> indices, QVector3D color = WHITE);

private:

    void deleteFaces() {for (int i = 0; i < m_faces.size(); i++) delete m_faces[i]; m_faces.clear();}
    void deleteVertices() {for (int i = 0; i < m_vertices.size(); i++) delete m_vertices[i]; m_vertices.clear();}

    QList<PolyhedronVertex*> m_vertices;
    QList<PolyhedronFace*> m_faces;
    bool m_smoothNormals;

    // vertex buffer objects (VBO)
    QOpenGLBuffer m_vertexBuffer, m_indexBuffer;
    GLsizei m_indexNbr;

    bool m_buffersComputed;

    void updateBuffers();

    // function called
    void updateRendering() {initializeOpenGLFunctions(); update(); updateBuffers();}
};

#endif // POLYHEDRA_H
