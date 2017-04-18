#include "Polyhedron.h"


PolyhedronVertex::PolyhedronVertex(double x, double y, double z) :
    position(QVector3D(x, y, z))
{}

PolyhedronVertex::PolyhedronVertex(QVector3D position) :
    position(position)
{}


PolyhedronFace::PolyhedronFace(QVector3D color) :
    color(color)
{}
