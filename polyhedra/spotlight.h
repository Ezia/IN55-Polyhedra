#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QMatrix4x4>
#include <QVector3D>

// Spot light based on a projective matrix
class SpotLight
{
public:
    SpotLight();

    void update();

    QMatrix4x4 getProjection() {return m_projection;}
    QVector3D getDirection() {return m_direction;}
    QVector3D getPosition() {return m_position;}
    QVector3D getUpDirection() {return m_upDirection;}
    float getVerticalAngle() {return m_verticalAngle;}
    float getHorizontalAngle() {return m_horizontalAngle;}
    float getNearPlan() {return m_nearPlan;}
    float getFarPlan() {return m_farPlan;}

    void setDirection(QVector3D direction) {m_direction = direction;}
    void setUpDirection(QVector3D upDirection) {m_upDirection = upDirection;}
    void setPosition(QVector3D position) {m_position = position;}
    void setVerticalAngle(float verticalAngle) {m_verticalAngle = verticalAngle;}
    void setHorizontalAngle(float horizontalAngle) {m_horizontalAngle = horizontalAngle;}
    void setNearPlan(float nearPlan) {m_nearPlan = nearPlan;}
    void setFarPlan(float farPlan) {m_farPlan = farPlan;}

private:
    // transform from world ref to projected light ref
    QMatrix4x4 m_projection;
    QVector3D m_direction, m_upDirection, m_position;
    float m_verticalAngle, m_horizontalAngle, m_nearPlan, m_farPlan;
};

#endif // SPOTLIGHT_H
