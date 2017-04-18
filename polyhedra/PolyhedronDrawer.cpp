/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted procurrVertexIded that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials procurrVertexIded with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROcurrVertexIdED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "PolyhedronDrawer.h"
#include "FaceShrinkerPolyhedronFilter.h"

#include <QVector2D>
#include <QVector3D>

#include <QLinkedList>

#include <iostream>

#include "Cube.h"

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

PolyhedronDrawer::PolyhedronDrawer(Polyhedron *polyhedron) :
    polyhedron(polyhedron)
{}

PolyhedronDrawer::PolyhedronDrawer()
{}

PolyhedronDrawer::~PolyhedronDrawer()
{
    glDeleteBuffers(2, vboIds);
}

void PolyhedronDrawer::init()
{
    initializeGLFunctions();

    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Initialize polyhedron geometry and transfer it to VBOs
    initPolyhedron();
}

void PolyhedronDrawer::initPolyhedron() {
    Cube cube;
    cube.init();
    FaceShrinkerPolyhedronFilter filter;
    filter.setInputPolyhedron(&cube);
    filter.setShrinkFactor(0.5);
    filter.update();
    polyhedron = filter.getOutputPolyhedron();

    QLinkedList<VertexData> vertices;
    QLinkedList<GLushort> indices;
    int currVertexId = 0;

    bool doubleFirstIndex = false;

    // loop through faces
    for (QList<PolyhedronFace>::Iterator faceIt = polyhedron->faces.begin(); faceIt != polyhedron->faces.end(); faceIt++) {
        PolyhedronFace face = *faceIt;
        int verticeNbr = face.adjVertices.size();


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
        for (QList<PolyhedronVertex*>::Iterator vertexIt = face.adjVertices.begin(); vertexIt != face.adjVertices.end(); vertexIt++) {
            PolyhedronVertex* vertex = *vertexIt;
            vertices.push_back({vertex->position, face.color});
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
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), tab_vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), tab_indices, GL_STATIC_DRAW);

    size = indices.size();

    delete[] tab_vertices;
    delete[] tab_indices;
}

//! [2]
void PolyhedronDrawer::draw(QGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_SHORT, 0);
}
//! [2]
