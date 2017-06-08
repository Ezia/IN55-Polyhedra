#include "FaceShrinkingFilter.h"

#include <QLinkedList>

#include "Polyhedron.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

FaceShrinkingFilter::FaceShrinkingFilter()
{
    this->m_input = NULL;
    this->m_output = NULL;
}

FaceShrinkingFilter::~FaceShrinkingFilter()
{
    if (m_output)
    {
        delete m_output;
    }
}

//============================= ATTRIBUTE ACCESSORS ==========================

void FaceShrinkingFilter::setFactor(float32 factor)
{
    this->m_factor = factor;
}

float32 FaceShrinkingFilter::factor() const
{
    return m_factor;
}

//============================= OPERATIONS ===================================

void FaceShrinkingFilter::update()
{

    QList<PolyhedronFace> newFaces;
    QList<PolyhedronVertex> newVertices;
    int32 vertexCounter = 0;

    if (this->m_output != NULL)
    {
        delete m_output;
        this->m_output = NULL;
    }

    if (m_factor == 1.)
    {
        m_output = new Polyhedron(*m_input);
    }
    else if (m_factor == 0.)
    {
        m_output = new Polyhedron(false);
    }
    else
    {
        m_output = new Polyhedron(false);

        // loop over faces
        for (int32 j = 0; j < m_input->getFaceNbr(); j++)
        {
            PolyhedronFace* face = m_input->getFace(j);

            //compute face centroid
            QVector3D centroid(0, 0, 0);
            int32 vertexNbr = face->getVertexNbr();
            for (int32 i = 0; i < face->getVertexNbr(); i++)
            {
                centroid = centroid + face->getVertex(i)->getPosition();
            }
            centroid = centroid / vertexNbr;

            // compute new vertices of the facec
            QList<PolyhedronVertex> tmp_face_vertices;
            QList<int32> vertices_indices;
            for (int32 i = 0; i < face->getVertexNbr(); i++)
            {
                PolyhedronVertex vertex = *face->getVertex(i);
                PolyhedronVertex new_vertex(centroid + (vertex.getPosition() - centroid)*m_factor);
                tmp_face_vertices.push_back(new_vertex);
                vertices_indices.push_back(vertexCounter);
                vertexCounter++;

            }
            m_output->addVertices(tmp_face_vertices);
            m_output->addFace(vertices_indices, face->getColor());
        }
    }

}
