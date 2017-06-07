#ifndef POLYHEDRONFILTER_H
#define POLYHEDRONFILTER_H

class Polyhedron;

class PolyhedronFilter
{
public:
    void setInput(Polyhedron* m_input);
    virtual void update() = 0;
    Polyhedron* getOutput();

protected:
    Polyhedron* m_input;
    Polyhedron* m_output;
};

#endif // POLYHEDRONFILTER_H
