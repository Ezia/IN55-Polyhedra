#include "MainWidget.h"

// motion
#include <QMouseEvent>

// math
#include <math.h>
#include "MVPMatrix.h"

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    angularSpeed(0)
{}

MainWidget::~MainWidget()
{}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Update scene
        update();
    }
}

void MainWidget::initializeGL()
{
    scene.init();

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 15.0, fov = 60.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);

    scene.setProjectionMatrix(projection);
    scene.setViewPortDImension({(float)w, (float)h});
    scene.setViewPortPosition({0, 0});
}

void MainWidget::paintGL()
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(0, 0, -10);
    viewMatrix.rotate(rotation);

    scene.setViewMatrix(viewMatrix);

    // *************************************************************
    // Uncomment to render the scene with basic shaders
    // *************************************************************

//    scene.drawBasic();

    // *************************************************************
    // Uncomment to render the scene with light and shadow
    // *************************************************************

    scene.drawRender();
}
