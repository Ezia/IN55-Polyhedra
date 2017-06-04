#ifndef FACESHRINKINGFILTER_H
#define FACESHRINKINGFILTER_H

#include "Polyhedron.h"
#include "PolyhedronFilter.h"

class FaceShrinkingFilter : public PolyhedronFilter
{

public:
    FaceShrinkingFilter();
    ~FaceShrinkingFilter();

    void setInput(Polyhedron* input);
    void update();
    Polyhedron* getOutput();

    // between 1 and 0, 1 leaving faces as they are
    void setFactor(double factor);

private:
    double factor;
};

#endif // FACESHRINKINGFILTER_H
