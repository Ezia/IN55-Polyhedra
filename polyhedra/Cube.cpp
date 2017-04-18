#include "Cube.h"

Cube::Cube() :
    x(0),
    y(0),
    z(0),
    xLength(1),
    yLength(1),
    zLength(1)
{}

void Cube::init()
{
    vertices.clear();
    faces.clear();

    vertices.push_back(PolyhedronVertex(x - xLength/2, y - yLength/2, z - zLength/2));
    vertices.push_back(PolyhedronVertex(x + xLength/2, y - yLength/2, z - zLength/2));
    vertices.push_back(PolyhedronVertex(x + xLength/2, y - yLength/2, z + zLength/2));
    vertices.push_back(PolyhedronVertex(x - xLength/2, y - yLength/2, z + zLength/2));

    vertices.push_back(PolyhedronVertex(x - xLength/2, y + yLength/2, z - zLength/2));
    vertices.push_back(PolyhedronVertex(x + xLength/2, y + yLength/2, z - zLength/2));
    vertices.push_back(PolyhedronVertex(x + xLength/2, y + yLength/2, z + zLength/2));
    vertices.push_back(PolyhedronVertex(x - xLength/2, y + yLength/2, z + zLength/2));

    faces.push_back(PolyhedronFace(RED));
    faces.push_back(PolyhedronFace(GREEN));
    faces.push_back(PolyhedronFace(BLUE));
    faces.push_back(PolyhedronFace(PURPLE));
    faces.push_back(PolyhedronFace(YELLOW));
    faces.push_back(PolyhedronFace(TURQUOISE));

    faces[0].adjVertices = {&vertices[0], &vertices[1], &vertices[2], &vertices[3]};
    faces[1].adjVertices = {&vertices[2], &vertices[6], &vertices[7], &vertices[3]};
    faces[2].adjVertices = {&vertices[1], &vertices[5], &vertices[6], &vertices[2]};
    faces[3].adjVertices = {&vertices[7], &vertices[4], &vertices[0], &vertices[3]};
    faces[4].adjVertices = {&vertices[4], &vertices[5], &vertices[1], &vertices[0]};
    faces[5].adjVertices = {&vertices[5], &vertices[4], &vertices[7], &vertices[6]};
}

void Cube::setPosition(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Cube::setDimension(double xLength, double yLength, double zLength)
{
    this->xLength = xLength;
    this->yLength = yLength;
    this->zLength = zLength;
}
