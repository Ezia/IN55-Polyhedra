#ifndef CUBE_H
#define CUBE_H

#include "Polyhedron.h"

class Cube : public Polyhedron
{
public:
    Cube();

    void init();

    void setPosition(double x, double y, double z);
    void setDimension(double xLength, double yLength, double zLength);

private:
    double x, y, z; // center of the cube
    double xLength, yLength, zLength;
};

#endif // CUBE_H
