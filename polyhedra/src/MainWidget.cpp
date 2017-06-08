#include "MainWidget.h"

// motion
#include <QMouseEvent>

// math
#include <math.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_angularSpeed(0)
{}

MainWidget::~MainWidget()
{}

//============================= OPERATIONS ===================================

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    m_mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - m_mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    m_rotationAxis = (m_rotationAxis * m_angularSpeed + n * acc).normalized();

    // Increase angular speed
    m_angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    m_angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (m_angularSpeed < 0.01)
    {
        m_angularSpeed = 0.0;
    }
    else
    {
        // Update rotation
        m_rotation = QQuaternion::fromAxisAndAngle(m_rotationAxis, m_angularSpeed) * m_rotation;

        // Update scene
        update();
    }
}

void MainWidget::initializeGL()
{
    m_scene.init();

    // Use QBasicTimer because its faster than QTimer
    m_timer.start(12, this);
}

void MainWidget::resizeGL(int32 w, int32 h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal z_near = 1.0, z_far = 15.0, fov = 60.0;

    // Reset projection
    m_projection.setToIdentity();

    // Set perspective projection
    m_projection.perspective(fov, aspect, z_near, z_far);

    m_scene.setProjectionMatrix(m_projection);
    m_scene.setViewPortDImension({(float32)w, (float32)h});
    m_scene.setViewPortPosition({0, 0});
}

void MainWidget::paintGL()
{
    QMatrix4x4 view_matrix;
    view_matrix.setToIdentity();
    view_matrix.translate(0, 0, -8);
    view_matrix.rotate(m_rotation);

    m_scene.setViewMatrix(view_matrix);

    // *************************************************************
    // Uncomment to render the scene with basic shaders
    // *************************************************************

//    scene.drawBasic();

    // *************************************************************
    // Uncomment to render the scene with light and shadow
    // *************************************************************

    m_scene.drawRender();
}

void MainWidget::cursorMoved(int value)
{
    // TODO
}
