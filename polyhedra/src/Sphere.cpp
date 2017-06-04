#include<math.h>

#include "Sphere.h"

void Sphere::update()
{
    if (!m_upToDate) {
        removeAll();

        int vertexCounter = 0;

        for (int i = 0 ; i < m_xyResolution ; i++) {
            float xyTheta1 = 2*M_PI * ((float) i / m_xyResolution);
            float xyTheta2 = 2*M_PI * ((float) (i+1.) / m_xyResolution);
            for (int j = 0 ; j < m_xzResolution ; j++) {
                float xzTheta1 = -M_PI_2 + (M_PI * ((float) j / m_xzResolution));
                float xzTheta2 = -M_PI_2 + (M_PI * ((float) (j+1.) / m_xzResolution));

                float projectedRadius1 = m_radius * cos(xzTheta1);
                float projectedRadius2 = m_radius * cos(xzTheta2);

                addVertex(PolyhedronVertex({projectedRadius1 * sin(xyTheta1) + m_position.x(),
                                            projectedRadius1 * cos(xyTheta1) + m_position.y(),
                                            m_radius * sin(xzTheta1) + m_position.z()}));
                addVertex(PolyhedronVertex({projectedRadius1 * sin(xyTheta2) + m_position.x(),
                                            projectedRadius1 * cos(xyTheta2) + m_position.y(),
                                            m_radius * sin(xzTheta1) + m_position.z()}));
                addVertex(PolyhedronVertex({projectedRadius2 * sin(xyTheta1) + m_position.x(),
                                            projectedRadius2 * cos(xyTheta1) + m_position.y(),
                                            m_radius * sin(xzTheta2) + m_position.z()}));
                addVertex(PolyhedronVertex({projectedRadius2 * sin(xyTheta2) + m_position.x(),
                                            projectedRadius2 * cos(xyTheta2) + m_position.y(),
                                            m_radius * sin(xzTheta2) + m_position.z()}));

                addFace({vertexCounter, vertexCounter+3, vertexCounter+1});
                addFace({vertexCounter, vertexCounter+2, vertexCounter+3});

                vertexCounter += 4;
            }
        }

        m_upToDate = true;
    }
}
