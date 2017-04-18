#ifndef FACESHRINKERPOLYHEDRONFILTER_H
#define FACESHRINKERPOLYHEDRONFILTER_H

#include "Polyhedron.h"

class FaceShrinkerPolyhedronFilter
{
public:
    FaceShrinkerPolyhedronFilter();
    ~FaceShrinkerPolyhedronFilter();

    void setInputPolyhedron(Polyhedron* input);
    // between 1 and 0, 0 leaving faces ase they are
    void setShrinkFactor(double factor);
    Polyhedron* getOutputPolyhedron();
    void update();

private:
    Polyhedron* input;
    Polyhedron* output;
    double factor;
};

#endif // FACESHRINKERPOLYHEDRONFILTER_H