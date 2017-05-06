#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Light : public QOpenGLFunctions
{
public:
    Light();
    ~Light();

    void setPosition(QVector3D position);
    void setDiffuse(QVector3D diffuse);
    void setAmbiant(QVector3D ambiant);

    QVector3D getPosition();
    QVector3D getDIffuse();
    QVector3D getAmbiant();

    void init();
    void update();

    void draw(QOpenGLShaderProgram *program);

private:
    QVector3D m_position, m_diffuse, m_ambiant;
    GLuint m_textureBuf;
    GLuint m_vbo[2];
};

#endif // LIGHT_H
