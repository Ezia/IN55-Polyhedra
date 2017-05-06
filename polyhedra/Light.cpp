#include "Light.h"

//#include "soil/src/SOIL.h"

Light::Light() :
    m_position(0, 0, 0),
    m_diffuse(0.8, 0.8, 0.8),
    m_ambiant(0.1, 0.1, 0.1)
{
}

Light::~Light()
{
    glDeleteTextures(1, &m_textureBuf);
    glDeleteBuffers(2, m_vbo);
}

void Light::setPosition(QVector3D position)
{
    m_position = position;
}

void Light::setDiffuse(QVector3D diffuse)
{
    m_diffuse = diffuse;
}

void Light::setAmbiant(QVector3D ambiant)
{
    m_ambiant = ambiant;
}

QVector3D Light::getPosition()
{
    return m_position;
}

QVector3D Light::getDIffuse()
{
    return m_diffuse;
}

QVector3D Light::getAmbiant()
{
    return m_ambiant;
}

void Light::init()
{
    initializeGLFunctions();

    glGenBuffers(2, m_vbo);

    int width, height;
//    unsigned char* image = SOIL_load_image("polyhedron_texture.png", &width, &height, 0, SOIL_LOAD_RGB);
//    glGenTextures(1, &m_textureBuf);
//    glBindTexture(GL_TEXTURE_2D, m_textureBuf);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
//                  GL_UNSIGNED_BYTE, image);
//    SOIL_free_image_data(image);
}

void Light::update()
{
    GLfloat position[3] = {m_position.x(), m_position.y(), m_position.z()};

    GLushort index[1] = {0};


    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), position, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort), index, GL_STATIC_DRAW);
}

void Light::draw(QGLShaderProgram *program)
{
    program->setUniformValue("a_light", true);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[1]);

    // Texture
    glBindTexture(GL_TEXTURE_2D, m_textureBuf);
//    glUniform1i(program->uniformLocation("a_texLight"), m_textureBuf);

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, 0);
}
