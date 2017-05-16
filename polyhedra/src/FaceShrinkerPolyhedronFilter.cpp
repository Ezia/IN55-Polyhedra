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
//    output->removeAll();

//    QList<PolyhedronFace> newFaces;
//    QList<PolyhedronVertex> newVertices;

//    if (factor == 1.) {
//        return;
//    } else if (factor == 1.) {
        // copy
//    } else
//{
        // loop over faces
//        for (int j = 0; j < input->getFaceNbr(); j++) {
//            PolyhedronFace* face = input->getFace(j);

//            //compute face centroid
//            QVector3D centroid(0, 0, 0);
//            int vertexNbr = face->getVertexNbr();
//            for (int i = 0; i < face->getVertexNbr(); i++) {
//                centroid = centroid + face->getVertex(i)->getPosition();
//            }
//            centroid = centroid / vertexNbr;

//            // compute new vertices of the face
//            PolyhedronFace newFace;
//            newFace.setColor(face->getColor());
//            QList<PolyhedronVertex*> tmpFaceVertices;
//            for (int i = 0; i < face->getVertexNbr(); i++) {
//                PolyhedronVertex vertex = *face->getVertex(i);
//                PolyhedronVertex newVertex(centroid + (vertex.getPosition() - centroid)*factor);
//                newVertices.push_back(newVertex);
//                tmpFaceVertices.push_back(&newVertices.back());
////                newFace.addVertex(&newVertices.back());
//            }
//            newFace.setVertices(tmpFaceVertices);
//            newFaces.push_back(newFace);
//        }
//    }

//    output->addFaces(newFaces);
//    output->addVertices(newVertices);
}
