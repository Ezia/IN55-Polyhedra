#ifndef FACESHRINKINGFILTER_H
#define FACESHRINKINGFILTER_H

#include "PolyhedronFilter.h"
#include "Types.h"

class FaceShrinkingFilter : public PolyhedronFilter
{
public:
    FaceShrinkingFilter();
    ~FaceShrinkingFilter();

    virtual void update();

    // between 1 and 0, 1 leaving faces as they are
    void setFactor(float32 factor);
    float32 factor() const;

private:
    float32 m_factor;
};

#endif // FACESHRINKINGFILTER_H
