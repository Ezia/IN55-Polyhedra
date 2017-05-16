#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "Scene.h"

// math
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>

// open gl
#include <QOpenGLFramebufferObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class MainWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    virtual ~MainWidget();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    // motion and redering matrice
    QBasicTimer timer;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    QMatrix4x4 projection;

    // scene
    Scene scene;
};

#endif // MAINWIDGET_H
