#include "Polyhedron.h"

#include <QLinkedList>

struct VertexData {
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Polyhedron::Polyhedron(bool smoothNormals, QList<PolyhedronVertex> vertices) :
    m_vertices(),
    m_faces(),
    m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_indexBuffer(QOpenGLBuffer::IndexBuffer),
    m_indexNbr(0),
    m_buffersComputed(false),
    m_smoothNormals(smoothNormals)
{
    addVertices(vertices);
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
    for (int32 i = 0; i < polyhedron.m_vertices.size(); i++)
    {
        m_vertices.append(new PolyhedronVertex(*polyhedron.m_vertices[i]));
    }

    for (int32 i = 0; i < polyhedron.m_faces.size(); i++)
    {
        PolyhedronFace* face = polyhedron.m_faces[i];
        QList<PolyhedronVertex*> face_vertices;
        for (int32 j = 0; j < face->getVertexNbr(); j++)
        {
            face_vertices.append(m_vertices[polyhedron.m_vertices.indexOf(face->getVertex(j))]);
        }
        m_faces.append(new PolyhedronFace(face_vertices, face->getColor()));
    }
}

Polyhedron::~Polyhedron()
{
    removeAll();
}

//============================= OPERATORS ====================================

Polyhedron &Polyhedron::operator=(const Polyhedron &polyhedron)
{
    removeAll();

    m_smoothNormals = polyhedron.m_smoothNormals;

    for (int32 i = 0; i < polyhedron.m_vertices.size(); i++)
    {
        m_vertices.append(new PolyhedronVertex(*polyhedron.m_vertices[i]));
    }

    for (int32 i = 0; i < polyhedron.m_faces.size(); i++)
    {
        PolyhedronFace* face = polyhedron.m_faces[i];
        QList<PolyhedronVertex*> face_vertices;
        for (int32 j = 0; j < face->getVertexNbr(); j++)
        {
            face_vertices.append(m_vertices[polyhedron.m_vertices.indexOf(face->getVertex(j))]);
        }
        m_faces.append(new PolyhedronFace(face_vertices, face->getColor()));
    }

    m_buffersComputed = false;

    return *this;
}

//============================= ATTRIBUTE ACCESSORS ==========================

int32 Polyhedron::getVertexNbr() const
{
    return m_vertices.size();
}

int32 Polyhedron::getFaceNbr() const
{
    return m_faces.size();
}

PolyhedronFace *Polyhedron::getFace(int32 id) const
{
    assert(id >= 0 && id < m_faces.size());
    return m_faces[id];
}

PolyhedronVertex *Polyhedron::getVertex(int32 id) const
{
    assert(id >= 0 && id < m_vertices.size());
    return m_vertices[id];
}

void Polyhedron::addFace(QList<int32> indices, QVector3D color)
{
    PolyhedronFace* new_face = new PolyhedronFace(color);
    for (int32 i = 0; i < indices.size(); i++)
    {
        new_face->addVertex(getVertex(indices[i]));
    }
    m_faces.append(new_face);

    m_buffersComputed = false;
}



void Polyhedron::removeAll()
{
    removeAllFaces();
    for (int32 i = 0; i < m_vertices.size(); i++)
    {
        delete m_vertices[i];
        m_vertices.removeAt(i);
        m_buffersComputed = false;
    }
}

void Polyhedron::removeAllFaces()
{
    for (int32 i = 0; i < m_faces.size(); i++)
    {
        removeFace(i);
    }
}

void Polyhedron::removeFace(int32 id)
{
    assert(id >= 0 && id < m_faces.size());
    delete m_faces[id];
    m_faces.removeAt(id);
    m_buffersComputed = false;
}

void Polyhedron::setVertices(QList<PolyhedronVertex> vertices)
{
    removeAll();
    addVertices(vertices);
}

void Polyhedron::addVertex(PolyhedronVertex vertex)
{
    m_vertices.push_back(new PolyhedronVertex(vertex));
    m_buffersComputed = false;
}

void Polyhedron::addVertices(QList<PolyhedronVertex> vertices)
{
    for (int32 i = 0; i < vertices.size(); i++)
    {
        addVertex(vertices[i]);
    }
}

//============================= OPERATIONS ===================================

void Polyhedron::setGeometryColor(QVector3D color)
{
    updateGeometry();
    for (int32 i = 0; i < m_faces.size(); i++)
    {
        m_faces[i]->setColor(color);
    }
    m_buffersComputed = false;
}

void Polyhedron::updateGeometry()
{}

void Polyhedron::drawRender(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int32 offset = 0;
    // Space between positions
    int32 stride = sizeof(VertexData);

    int32 vertexPositionLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int32 vertexColorLoc = program->attributeLocation("a_color");
    program->enableAttributeArray(vertexColorLoc);
    program->setAttributeBuffer(vertexColorLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int32 vertexNormalLoc = program->attributeLocation("a_normal");
    program->enableAttributeArray(vertexNormalLoc);
    program->setAttributeBuffer(vertexNormalLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_INT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

void Polyhedron::drawShadow(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int32 offset = 0;
    // Space between positions
    int32 stride = sizeof(VertexData);

    int32 vertexPositionLoc = program->attributeLocation("in_position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_INT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

void Polyhedron::drawBasic(QOpenGLShaderProgram *program)
{
    updateRendering();

    m_indexBuffer.bind();
    m_vertexBuffer.bind();

    // Offset for position
    int32 offset = 0;
    // Space between positions
    int32 stride = sizeof(VertexData);

    int32 vertexPositionLoc = program->attributeLocation("position");
    program->enableAttributeArray(vertexPositionLoc);
    program->setAttributeBuffer(vertexPositionLoc, GL_FLOAT, offset, 3, stride);

    offset += sizeof(QVector3D);

    int32 vertexColorLoc = program->attributeLocation("in_color");
    program->enableAttributeArray(vertexColorLoc);
    program->setAttributeBuffer(vertexColorLoc, GL_FLOAT, offset, 3, stride);

    glDrawElements(GL_TRIANGLE_STRIP, m_indexNbr, GL_UNSIGNED_INT, 0);

    m_indexBuffer.release();
    m_vertexBuffer.release();
}

/////////////////////////////// PRIVATE    ///////////////////////////////////

//============================= OPERATIONS ===================================

void Polyhedron::updateBuffers()
{
    if (!m_buffersComputed)
    {
        if (!m_indexBuffer.isCreated())
        {
            m_indexBuffer.create();
        }

        if (!m_vertexBuffer.isCreated())
        {
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
        QLinkedList<uint> indices;
        int32 curr_vertex_id = 0;

        bool double_first_index = false;

        // loop through faces
        for (int32 i = 0; i < m_faces.size(); i++)
        {
            PolyhedronFace* face = m_faces[i];

            // Add vertices to list
            for ( int32 j = 0; j < face->getVertexNbr(); j++)
            {
                PolyhedronVertex* vertex = face->getVertex(j);
                if (m_smoothNormals)
                {
                    vertices.push_back({vertex->getPosition(), face->getColor(), vertex->getNormal()});
                }
                else
                {
                    vertices.push_back({vertex->getPosition(), face->getColor(), face->getNormal()});
                }
            }

            // Add indices to list

//            if (doubleFirstIndex)
//            {
                indices.push_back(curr_vertex_id);
//            }
            indices.push_back(curr_vertex_id);

            int32 incr_index_value = 1;
            int32 index_added_nbr = 1;
            while (index_added_nbr < face->getVertexNbr())
            {
                if (index_added_nbr%2 == 0)
                {
                    indices.push_back(curr_vertex_id+face->getVertexNbr()-incr_index_value);
                    incr_index_value++;
                }
                else
                {
                    indices.push_back(curr_vertex_id+incr_index_value);
                }
//                doubleFirstIndex = !doubleFirstIndex;
                index_added_nbr++;
            }

            curr_vertex_id += face->getVertexNbr();

            // double last index
            indices.push_back(indices.last());

            // update vertex index
//            doubleFirstIndex = face->getVertexNbr()%2 != 0;
        }

        // remove last index
        indices.pop_back();

        // Transfer to arrays

        VertexData tab_vertices[vertices.size()];
        int32 tab_indices[indices.size()];

        int32 i = 0;
        for (QLinkedList<VertexData>::Iterator it = vertices.begin(); it != vertices.end(); it++)
        {
            tab_vertices[i++] = (*it);
        }
        i = 0;
        for (QLinkedList<uint>::Iterator it = indices.begin(); it != indices.end(); it++)
        {
            tab_indices[i++] = (*it);
        }

        // Transfer vertices to buffer
        m_vertexBuffer.bind();
        m_vertexBuffer.allocate(tab_vertices, vertices.size() * sizeof(VertexData));
        m_vertexBuffer.release();


        // Transfer indices to buffer
        m_indexBuffer.bind();
        m_indexBuffer.allocate(tab_indices, indices.size() * sizeof(uint));
        m_indexBuffer.release();

        m_indexNbr = indices.size();

        m_buffersComputed = true;
    }
}

void Polyhedron::updateRendering() {
    initializeOpenGLFunctions();
    updateGeometry();
    updateBuffers();
}
