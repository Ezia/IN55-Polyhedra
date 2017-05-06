
#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>
#include <locale.h>

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent),
    angularSpeed(0)
{
}

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
        updateGL();
    }
}

void MainWidget::initializeGL()
{
    initializeGLFunctions();
    qglClearColor(Qt::black);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
//    glEnable(GL_CULL_FACE);

    scene.init();

    fbo = new QGLFramebufferObject(width(), height());

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
//    QGLShader vshader(QGLShader::Vertex, this);
//    vshader.compileSourceFile(":/vshader.glsl");

//    QGLShader fshader(QGLShader::Fragment, this);
//    fshader.compileSourceFile(":/fshader.glsl");

    programPainter.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl");
    programPainter.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl");
    programPainter.link();

    programShadowProjection.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl");
    programShadowProjection.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl");
    programShadowProjection.link();


//    // Compile vertex shader
//    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
//        close();

//    // Compile fragment shader
//    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
//        close();

//    // Link shader pipeline
//    if (!program.link())
//        close();

//    // Bind shader pipeline for use
//    if (!program.bind())
//        close();
}

void MainWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    programPainter.bind();

//    fbo->bind();

//    glBindTexture(GL_TEXTURE_2D, 0);

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    programPainter.setUniformValue("mvp_matrix", projection * matrix);
    programPainter.setUniformValue("mv_matrix", matrix);

    // Draw scene
    scene.draw(&programPainter);

//    fbo->release();
}

MainWidget0::MainWidget0(QWidget *parent)
{

}

MainWidget0::~MainWidget0()
{

}
