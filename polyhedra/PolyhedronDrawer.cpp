#include "PolyhedronDrawer.h"

#include "FaceShrinkerPolyhedronFilter.h"

#include <QVector2D>
#include <QVector3D>

#include <QLinkedList>

#include <iostream>

#include "Cube.h"
#include <assert.h>

struct VertexData
{
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

PolyhedronDrawer::PolyhedronDrawer()
{
}

PolyhedronDrawer::~PolyhedronDrawer()
{
    glDeleteBuffers(2, m_vboIds);
}

void PolyhedronDrawer::init()
{
    initializeGLFunctions();

     // Generate 2 VBOs
     glGenBuffers(2, m_vboIds);

}

void PolyhedronDrawer::setPolyhedron(Polyhedron *polyhedron)
{
    m_polyhedron = polyhedron;
}

void PolyhedronDrawer::update()
{
    // Initialize polyhedron geometry and transfer it to VBOs
     updatePolyhedron();
}

void PolyhedronDrawer::updatePolyhedron() {
    // TODO check null pointers for polyhedron
    m_polyhedron->computeNormals();

    QLinkedList<VertexData> vertices;
    QLinkedList<GLushort> indices;
    int currVertexId = 0;

    bool doubleFirstIndex = false;

    // loop through faces
    for (int i = 0; i < m_polyhedron->getFaceNbr(); i++) {
        PolyhedronFace face = m_polyhedron->getFace(i);
        int verticeNbr = face.getAdjVertexNbr();


        // Indices for drawing cube faces using triangle strips.
        // Triangle strips can be connected by duplicating indices
        // between the strips. If connecting strips have opposite
        // vertex order then last index of the first strip and first
        // index of the second strip needs to be duplicated. If
        // connecting strips have same vertex order then only last
        // index of the first strip needs to be duplicated.

        // Add indices to list
        int incrIndexValue = 1;
        int indexAddedNbr = 1;

        if (doubleFirstIndex){
            indices.push_back(currVertexId);
        }
        indices.push_back(currVertexId);

        while (indexAddedNbr < verticeNbr) {
            if (indexAddedNbr%2 == 0) {
                indices.push_back(currVertexId+verticeNbr-incrIndexValue);
                incrIndexValue++;
            } else {
                indices.push_back(currVertexId+incrIndexValue);
            }
            indexAddedNbr++;
        }

        currVertexId += verticeNbr;

        // double last index
        indices.push_back(indices.last());

        // Add vertices to list
        for ( int i = 0; i < face.getAdjVertexNbr(); i++) {
            PolyhedronVertex* vertex = face.getAdjVertex(i);
            vertices.push_back({vertex->getPosition(), face.getColor(), face.getNormal()});
        }

        // update vertex index
        doubleFirstIndex = verticeNbr%2 == 0;
    }

    indices.pop_back();

    // Transfer to arrays
    VertexData* tab_vertices = new VertexData[vertices.size()];
    GLushort* tab_indices = new GLushort[indices.size()];

    int i = 0;
    for (QLinkedList<VertexData>::Iterator it = vertices.begin(); it != vertices.end(); it++) {
        tab_vertices[i++] = (*it);
    }
    i = 0;
    for (QLinkedList<GLushort>::Iterator it = indices.begin(); it != indices.end(); it++) {
        tab_indices[i++] = (*it);
    }

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), tab_vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), tab_indices, GL_STATIC_DRAW);

    m_indexNbr = indices.size();

    delete[] tab_vertices;
    delete[] tab_indices;
}

//! [2]
void PolyhedronDrawer::draw(QGLShaderProgram *program)
{
    // lightning
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat position[] = { 1, 1, 0.5, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);


    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int normalLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_SHORT, 0);
}
//! [2]
