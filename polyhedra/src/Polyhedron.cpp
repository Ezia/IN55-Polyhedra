#include "Polyhedron.h"

#include <QLinkedList>

struct VertexData {
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

void PolyhedronFace::computeNormal()
{
    assert(m_vertices.size() >= 3);
    QVector3D v1 = m_vertices[1]->getPosition() - m_vertices[0]->getPosition();
    QVector3D v2 = m_vertices[2]->getPosition() - m_vertices[1]->getPosition();
    m_normal = QVector3D::crossProduct(v1, v2).normalized();
    m_normalComputed = true;
}


Polyhedron::Polyhedron(Polyhedron const& polyhedron) :
    QOpenGLFunctions(),
    m_vertices(),
    m_faces(),
    m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_indexBuffer(QOpenGLBuffer::IndexBuffer),
    m_indexNbr(0),
    m_buffersComputed(false),
    m_smoothNormals(polyhedron.m_smoothNormals)
{
    for (int i = 0; i < polyhedron.m_vertices.size(); i++) {
        m_vertices.append(new PolyhedronVertex(*polyhedron.m_vertices[i]));
    }

    for (int i = 0; i < polyhedron.m_faces.size(); i++) {
        PolyhedronFace* face = polyhedron.m_faces[i];
        QList<PolyhedronVertex*> faceVertices;
        for (int j = 0; j < face->getVertexNbr(); j++) {
            faceVertices.append(m_vertices[polyhedron.m_vertices.indexOf(face->getVertex(j))]);
        }
        m_faces.append(new PolyhedronFace(faceVertices, face->getColor()));
    }
}

Polyhedron &Polyhedron::operator=(const Polyhedron &polyhedron)
{
    removeAll();

    m_smoothNormals = polyhedron.m_smoothNormals;

    for (int i = 0; i < polyhedron.m_vertices.size(); i++) {
        m_vertices.append(new PolyhedronVertex(*polyhedron.m_vertices[i]));
    }

    for (int i = 0; i < polyhedron.m_faces.size(); i++) {
        PolyhedronFace* face = polyhedron.m_faces[i];
        QList<PolyhedronVertex*> faceVertices;
        for (int j = 0; j < face->getVertexNbr(); j++) {
            faceVertices.append(m_vertices[polyhedron.m_vertices.indexOf(face->getVertex(j))]);
        }
        m_faces.append(new PolyhedronFace(faceVertices, face->getColor()));
    }

    m_buffersComputed = false;

    return *this;
}

void Polyhedron::addFace(QList<int> indices, QVector3D color)
{
    PolyhedronFace* newFace = new PolyhedronFace(color);
    for (int i = 0; i < indices.size(); i++) {
        newFace->addVertex(getVertex(indices[i]));
    }
    m_faces.append(newFace);

    m_buffersComputed = false;
}

void Polyhedron::drawRender(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int offset = 0;
    // Space between positions
    int stride = sizeof(VertexData);

    int vertexPositionLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int vertexColorLoc = program->attributeLocation("a_color");
    program->enableAttributeArray(vertexColorLoc);
    program->setAttributeBuffer(vertexColorLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int vertexNormalLoc = program->attributeLocation("a_normal");
    program->enableAttributeArray(vertexNormalLoc);
    program->setAttributeBuffer(vertexNormalLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_SHORT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

void Polyhedron::drawShadow(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int offset = 0;
    // Space between positions
    int stride = sizeof(VertexData);

    int vertexPositionLoc = program->attributeLocation("in_position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_SHORT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

void Polyhedron::drawBasic(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int offset = 0;
    // Space between positions
    int stride = sizeof(VertexData);

    int vertexPositionLoc = program->attributeLocation("position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int vertexColorLoc = program->attributeLocation("in_color");
    program->enableAttributeArray(vertexColorLoc);
    program->setAttributeBuffer(vertexColorLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_SHORT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

void Polyhedron::updateBuffers()
{
    if (!m_buffersComputed) {
        if (!m_indexBuffer.isCreated()) {
            m_indexBuffer.create();
        }

        if (!m_vertexBuffer.isCreated()) {
            m_vertexBuffer.create();
        }

        // Indices for drawing cube faces using triangle strips.
        // Triangle strips can be connected by duplicating indices
        // between the strips. If connecting strips have opposite
        // vertex order then last index of the first strip and first
        // index of the second strip needs to be duplicated. If
        // connecting strips have same vertex order then only last
        // index of the first strip needs to be duplicated.

        QLinkedList<VertexData> vertices;
        QLinkedList<GLushort> indices;
        int currVertexId = 0;

        bool doubleFirstIndex = false;

        // loop through faces
        for (int i = 0; i < m_faces.size(); i++) {
            PolyhedronFace* face = m_faces[i];

            // Add vertices to list
            for ( int j = 0; j < face->getVertexNbr(); j++) {
                PolyhedronVertex* vertex = face->getVertex(j);
                if (m_smoothNormals) {
                    vertex->getNormal();
                    vertices.push_back({vertex->getPosition(), face->getColor(), vertex->getNormal()});
                } else {
                    vertices.push_back({vertex->getPosition(), face->getColor(), face->getNormal()});
                }
            }

            // Add indices to list

            if (doubleFirstIndex){
                indices.push_back(currVertexId);
            }
            indices.push_back(currVertexId);

            int incrIndexValue = 1;
            int indexAddedNbr = 1;
            while (indexAddedNbr < face->getVertexNbr()) {
                if (indexAddedNbr%2 == 0) {
                    indices.push_back(currVertexId+face->getVertexNbr()-incrIndexValue);
                    incrIndexValue++;
                } else {
                    indices.push_back(currVertexId+incrIndexValue);
                }
                indexAddedNbr++;
            }

            currVertexId += face->getVertexNbr();

            // double last index
            indices.push_back(indices.last());

            // update vertex index
            doubleFirstIndex = face->getVertexNbr()%2 == 0;
        }

        // remove last index
        indices.pop_back();

        // Transfer to arrays

        VertexData tabVertices[vertices.size()];
        GLushort tabIndices[indices.size()];

        int i = 0;
        for (QLinkedList<VertexData>::Iterator it = vertices.begin(); it != vertices.end(); it++) {
            tabVertices[i++] = (*it);
        }
        i = 0;
        for (QLinkedList<GLushort>::Iterator it = indices.begin(); it != indices.end(); it++) {
            tabIndices[i++] = (*it);
        }

        // Transfer vertices to buffer
        m_vertexBuffer.bind();
        m_vertexBuffer.allocate(tabVertices, vertices.size() * sizeof(VertexData));
        m_vertexBuffer.release();


        // Transfer indices to buffer
        m_indexBuffer.bind();
        m_indexBuffer.allocate(tabIndices, indices.size() * sizeof(GLushort));
        m_indexBuffer.release();

        m_indexNbr = indices.size();

        m_buffersComputed = true;
    }
}

void PolyhedronVertex::computeNormal()
{
    assert(m_faces.size() > 0);
    m_normal[0] = 0;
    m_normal[1] = 0;
    m_normal[2] = 0;
    for (int i = 0; i < m_faces.size(); i++) {
        m_normal+= m_faces.at(i)->getNormal();
    }
    m_normal.normalize();
    m_normalComputed = true;
}
