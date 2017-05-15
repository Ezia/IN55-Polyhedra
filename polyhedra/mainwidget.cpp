#include "mainwidget.h"

// motion
#include <QMouseEvent>

// math
#include <math.h>
#include "mvpmatrix.h"

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    angularSpeed(0)
{}

MainWidget::~MainWidget()
{
    if (fbo) delete fbo;
}

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
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.1, 1);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
//    glEnable(GL_CULL_FACE);

    scene.init();


    fbo = new QOpenGLFramebufferObject(width(), height(), QOpenGLFramebufferObject::Depth);


    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    programPainter.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    programPainter.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    programPainter.link();

    programShadowProjection.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshadershadowmap.vsh");
    programShadowProjection.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshadershadowmap.fsh");
    programShadowProjection.link();

    testShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/basicshaderv.vsh");
    testShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/basicshaderf.fsh");
    testShader.link();
}

void MainWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 15.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    QMatrix4x4 MV;
    MV.setToIdentity();
    MV.translate(0, 0, -10);
    MV.rotate(rotation);

    // *************************************************************
    // Uncomment to render the scene with basic shaders
    // *************************************************************

//    testShader.bind();

//    testShader.setUniformValue("MVP", projection * MV);

//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    scene.drawTest(&testShader);

//    testShader.release();

    // *************************************************************
    // Uncomment to render the scene with light and shadow
    // *************************************************************

    programShadowProjection.bind();

    fbo->bind();

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.drawShadow(&programShadowProjection, projection);

    fbo->release();

    programShadowProjection.release();


    programPainter.bind();

    programPainter.setUniformValue("mvp_matrix", projection * MV);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo->texture());
    glEnable(GL_TEXTURE_2D);

    // Clear color and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw scene
    scene.draw(&programPainter, projection);

    programPainter.release();

}
