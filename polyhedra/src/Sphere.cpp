#include<math.h>

#include "Sphere.h"

void Sphere::update()
{
    if (!m_upToDate) {
        removeAll();

        addVertex(PolyhedronVertex({m_position.x(), m_position.y(), m_radius + m_position.z()}));

        for (int j = 1 ; j < m_xzResolution ; j++)
        {
            float xzTheta = M_PI_2 - (M_PI * ((float) j / m_xzResolution));
            float projectedRadius = m_radius * cos(xzTheta);

            for (int i = 0 ; i < m_xyResolution ; i++)
            {
                float xyTheta = 2*M_PI * ((float) i / m_xyResolution);

                addVertex(PolyhedronVertex({projectedRadius * cos(xyTheta) + m_position.x(),
                                            projectedRadius * sin(xyTheta) + m_position.y(),
                                            m_radius * sin(xzTheta) + m_position.z()}));
            }
        }

        addVertex(PolyhedronVertex({m_position.x(), m_position.y(), -m_radius + m_position.z()}));

        for (int i = 1 ; i < m_xyResolution ; i++)
        {
            addFace({0, i, i+1});
        }
        addFace({0, m_xyResolution, 1});

        for (int j = 0 ; j < m_xzResolution-2 ; j++)
        {
            for (int i = 1 ; i < m_xyResolution ; i++) {
                addFace({j*m_xyResolution + i,
                         (j+1)*m_xyResolution + i,
                         (j+1)*m_xyResolution + i + 1,
                         j*m_xyResolution + i + 1});
            }
            addFace({(j+1)*m_xyResolution,
                     (j+2)*m_xyResolution,
                     (j+1)*m_xyResolution + 1,
                     j*m_xyResolution + 1});
        }

        for (int i = 1 ; i < m_xyResolution ; i++)
        {
            addFace({(m_xzResolution-1)*m_xyResolution + 1,
                     (m_xzResolution-2)*m_xyResolution + i+1,
                     (m_xzResolution-2)*m_xyResolution + i});
        }
        addFace({(m_xzResolution-1)*m_xyResolution + 1,
                 (m_xzResolution-2)*m_xyResolution + 1,
                 (m_xzResolution-1)*m_xyResolution});

        m_upToDate = true;
    }
}
