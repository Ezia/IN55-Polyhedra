#include "FaceShrinkingFilter.h"

#include <QLinkedList>

FaceShrinkingFilter::FaceShrinkingFilter()
{
    this->input = NULL;
    this->output = NULL;
}

FaceShrinkingFilter::~FaceShrinkingFilter()
{
    if (output) {
        delete output;
    }
}

void FaceShrinkingFilter::setInput(Polyhedron *input)
{
    this->input = input;
}

void FaceShrinkingFilter::setFactor(double factor)
{
    this->factor = factor;
}

Polyhedron* FaceShrinkingFilter::getOutput()
{
    return output;
}

void FaceShrinkingFilter::update()
{

    QList<PolyhedronFace> newFaces;
    QList<PolyhedronVertex> newVertices;
    int vertexCounter = 0;

    if (this->output != NULL) {
        delete output;
        this->output = NULL;
    }

    if (factor == 1.)
    {
        output = new Polyhedron(*input);
    }
    else if (factor == 0.)
    {
        output = new Polyhedron();
    }
    else
    {
        output = new Polyhedron();
        // loop over faces
        for (int j = 0; j < input->getFaceNbr(); j++) {
            PolyhedronFace* face = input->getFace(j);

            //compute face centroid
            QVector3D centroid(0, 0, 0);
            int vertexNbr = face->getVertexNbr();
            for (int i = 0; i < face->getVertexNbr(); i++) {
                centroid = centroid + face->getVertex(i)->getPosition();
            }
            centroid = centroid / vertexNbr;

            // compute new vertices of the facec
            QList<PolyhedronVertex> tmpFaceVertices;
            QList<int> verticesIndices;
            for (int i = 0; i < face->getVertexNbr(); i++) {
                PolyhedronVertex vertex = *face->getVertex(i);
                PolyhedronVertex newVertex(centroid + (vertex.getPosition() - centroid)*factor);
                tmpFaceVertices.push_back(newVertex);
                verticesIndices.push_back(vertexCounter);
                vertexCounter++;

            }
            output->addVertices(tmpFaceVertices);
            output->addFace(verticesIndices, face->getColor());
        }
    }

}
