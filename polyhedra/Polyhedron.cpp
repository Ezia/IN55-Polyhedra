#include "Polyhedron.h"


PolyhedronVertex::PolyhedronVertex(double x, double y, double z) :
    position(QVector3D(x, y, z))
{}


PolyhedronFace::PolyhedronFace(QVector3D color) :
    color(color)
{}
