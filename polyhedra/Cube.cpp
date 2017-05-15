#include "Cube.h"

void Cube::update()
{
    if (!m_upToDate) {
        removeAll();

        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() - m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));

        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() - m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() + m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));
        addVertex(PolyhedronVertex({m_position.x() - m_dimension.x()/2, m_position.y() + m_dimension.y()/2, m_position.z() + m_dimension.z()/2}));

        addFace({0, 1, 2, 3});
        addFace({2, 6, 7, 3});
        addFace({1, 5, 6, 2});
        addFace({7, 4, 0, 3});
        addFace({4, 5, 1, 0});
        addFace({5, 4, 7, 6});

        m_upToDate = true;
    }
}
