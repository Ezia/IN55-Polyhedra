#include "FaceShrinkerPolyhedronFilter.h"

#include <QLinkedList>

FaceShrinkerPolyhedronFilter::FaceShrinkerPolyhedronFilter()
{
    output = new Polyhedron;
}

FaceShrinkerPolyhedronFilter::~FaceShrinkerPolyhedronFilter()
{
    delete output;
}

void FaceShrinkerPolyhedronFilter::setInputPolyhedron(Polyhedron *input)
{
    this->input = input;
}

void FaceShrinkerPolyhedronFilter::setShrinkFactor(double factor)
{
    this->factor = factor;
}

Polyhedron* FaceShrinkerPolyhedronFilter::getOutputPolyhedron()
{
    return output;
}

void FaceShrinkerPolyhedronFilter::update()
{
    output->vertices.clear();
    output->faces.clear();

    QList<PolyhedronFace> newFaces;
    QList<PolyhedronVertex> newVertices;

    if (factor == 0.) {
        return;
//    } else if (factor == 1.) {
        // copy
    } else {
        // loop over faces
        for (QList<PolyhedronFace>::Iterator faceIt = input->faces.begin(); faceIt != input->faces.end(); faceIt++) {
            PolyhedronFace face = *faceIt;

            //compute face centroid
            QVector3D centroid(0, 0, 0);
            int vertexNbr = face.adjVertices.size();
            for (QList<PolyhedronVertex*>::Iterator vertexIt = face.adjVertices.begin(); vertexIt != face.adjVertices.end();
                 vertexIt++) {
                centroid = centroid + (*vertexIt)->position;
            }
            centroid = centroid / vertexNbr;

            // compute new vertices of the face
            PolyhedronFace newFace(face.color);
            for (QList<PolyhedronVertex*>::Iterator vertexIt = face.adjVertices.begin(); vertexIt != face.adjVertices.end();
                 vertexIt++) {
                PolyhedronVertex vertex = **vertexIt;
                PolyhedronVertex newVertex(centroid + (vertex.position - centroid)*factor);
                newVertices.push_back(newVertex);
                newFace.adjVertices.push_back(&newVertices.back());
            }
            newFaces.push_back(newFace);
        }
    }

    output->faces = newFaces;
    output->vertices = newVertices;
}
