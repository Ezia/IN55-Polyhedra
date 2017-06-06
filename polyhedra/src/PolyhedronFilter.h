#ifndef POLYHEDRONFILTER_H
#define POLYHEDRONFILTER_H

#include "Polyhedron.h"

class PolyhedronFilter
{

public:
    virtual void setInput(Polyhedron* input) = 0;
    virtual void update() = 0;
    virtual Polyhedron* getOutput() = 0;

protected:
    Polyhedron* input;
    Polyhedron* output;
};

#endif // POLYHEDRONFILTER_H
