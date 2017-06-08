#ifndef MAINWIDGET_H
#define MAINWIDGET_H

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

#include "Scene.h"
#include "Types.h"

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
    void resizeGL(int32 w, int32 h);
    void paintGL();

private:
    // motion and redering matrice
    QBasicTimer m_timer;
    QVector2D m_mousePressPosition;
    QVector3D m_rotationAxis;
    qreal m_angularSpeed;
    QQuaternion m_rotation;
    QMatrix4x4 m_projection;

    // scene
    Scene m_scene;

private slots:
    void filterSliderUpdate(int value);
    void spotVerticalSliderUpdate(int value);
    void spotHorizontalSliderUpdate(int value);
};

#endif // MAINWIDGET_H
