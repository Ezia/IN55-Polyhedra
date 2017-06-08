#include "PolyhedronFilter.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= ATTRIBUTE ACCESSORS ==========================

void PolyhedronFilter::setInput(Polyhedron *input)
{
    this->m_input = input;
}

Polyhedron* PolyhedronFilter::getOutput()
{
    return m_output;
}

Polyhedron *PolyhedronFilter::getInput()
{
    return m_input;
}
