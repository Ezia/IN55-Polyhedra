#include<math.h>

#include "Sphere.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Sphere::Sphere(QVector3D position, float32 radius, int32 xyResolution, int32 xzResolution) :
    Polyhedron(true),
    m_position(position),
    m_radius(radius),
    m_xyResolution(xyResolution),
    m_xzResolution(xzResolution),
    m_upToDate(false)
{}

//============================= ATTRIBUTE ACCESSORS ==========================

QVector3D Sphere::getPosition() const
{
    return m_position;
}

float32 Sphere::getRadius() const
{
    return m_radius;
}

int32 Sphere::getXYResolution() const
{
    return m_xyResolution;
}

int32 Sphere::getXZResolution() const
{
    return m_xzResolution;
}

void Sphere::setPosition(QVector3D position)
{
    m_position = position ;
    m_upToDate = false;
}

void Sphere::setRadius(float32 radius)
{
    m_radius = radius ;
    m_upToDate = false;
}

void Sphere::setXYResolution(int32 xyResolution)
{
    m_xyResolution = xyResolution;
    m_upToDate = false;
}

void Sphere::setXZResolution(int32 xzResolution)
{
    m_xzResolution = xzResolution;
    m_upToDate = false;
}

//============================= OPERATIONS ===================================

void Sphere::updateGeometry()
{
    if (!m_upToDate)
    {
        removeAll();

        addVertex(PolyhedronVertex({m_position.x(), m_position.y(), m_radius + m_position.z()}));

        for (int32 j = 1 ; j < m_xzResolution ; j++)
        {
            float32 xz_theta = M_PI_2 - (M_PI * ((float32) j / m_xzResolution));
            float32 projected_radius = m_radius * cos(xz_theta);

            for (int32 i = 0 ; i < m_xyResolution ; i++)
            {
                float32 xy_theta = 2*M_PI * ((float32) i / m_xyResolution);

                addVertex(PolyhedronVertex({projected_radius * cos(xy_theta) + m_position.x(),
                                            projected_radius * sin(xy_theta) + m_position.y(),
                                            m_radius * sin(xz_theta) + m_position.z()}));
            }
        }

        addVertex(PolyhedronVertex({m_position.x(), m_position.y(), -m_radius + m_position.z()}));

        for (int32 i = 1 ; i < m_xyResolution ; i++)
        {
            addFace({0, i, i+1});
        }
        addFace({0, m_xyResolution, 1});

        for (int32 j = 0 ; j < m_xzResolution-2 ; j++)
        {
            for (int32 i = 1 ; i < m_xyResolution ; i++)
            {
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

        for (int32 i = 1 ; i < m_xyResolution ; i++)
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
