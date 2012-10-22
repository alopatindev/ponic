#include "Graphics.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "ImageManager.h"
#include "Log.h"
#include "Camera.h"
//#include "FontManager.h"
#include "misc/Utils.h"
#include "Assert.h"

GLuint shaderVertex,
       shaderFragment,
       shaderProgram;

GLuint uniformOrtho,
       uniformAngle,
       uniformScale,
       uniformPosition,
       uniformColor,
       uniformOpacity,
       uniformWithTexture,
       uniformPerspProjMat,
       attribVertex;

void initShaders();
void logShader(const char* tag, GLuint i);

void Graphics_Class::init()
{
    initShaders();
}

void Graphics_Class::startFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics_Class::endFrame()
{
    flushGeomerty(m_imagesBuffer);
    flushGeomerty(m_imagesBufferTransparent);
//    glutSwapBuffers();
}

void Graphics_Class::forceRedraw()
{
//    glutPostRedisplay();
}

void Graphics_Class::onReshape(int width, int height)
{
    m_width = (float)width;
    m_height = (float)height;

    float perspMatrix[16];
    float aspect = m_width / m_height;
    buildPerspProjMat(perspMatrix, 45.0f, aspect, ZNEAR, ZFAR);
    glUniformMatrix4fv(uniformPerspProjMat, 1, GL_FALSE, perspMatrix);

    glViewport(0, 0, width, height);
}

void Graphics_Class::flushRectangle2D(const Command* c)
{
    GLfloat xOffset = -c->centerX * c->width;
    GLfloat yOffset = -c->centerY * c->height;

    GLfloat verts[] = {0.0f + xOffset,  c->height + yOffset,
                       c->width + xOffset, c->height + yOffset,
                       c->width + xOffset, 0.0f + yOffset,

                       0.0f + xOffset,  c->height + yOffset,
                       0.0f + xOffset,  0.0f + yOffset,
                       c->width + xOffset, 0.0f + yOffset};

    glUniform1f(uniformOrtho, true);

    float position[4];
    position[0] = c->x - xOffset;
    position[1] = c->y - yOffset;
    position[2] = 0.0f;
    position[3] = 0.0f;
    glUniform4fv(uniformPosition, 1, position);

    glUniform1f(uniformAngle, c->angle);

    glUniform1f(uniformScale, c->scaleFactor);

    glUniform3fv(uniformColor, 1, c->color);

    glUniform1f(uniformOpacity, c->opacity);

    glUniform1f(uniformWithTexture, false);

    glVertexAttribPointer(attribVertex, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glEnableVertexAttribArray(attribVertex);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, verts); // FIXME
    glDrawElements(GL_LINES, 12, GL_UNSIGNED_SHORT, verts);
}

void Graphics_Class::flushImage2D(const Command* c)
{
    Image* image = ImageManager::getInstance().bindImage(c->group.c_str(),
                                                         c->name.c_str());

    GLfloat xOffset = -c->centerX * c->width;
    GLfloat yOffset = -c->centerY * c->height;

    GLfloat verts[] = {0.0f + xOffset,  c->height + yOffset,
                       c->width + xOffset, c->height + yOffset,
                       c->width + xOffset, 0.0f + yOffset,

                       0.0f + xOffset,  c->height + yOffset,
                       0.0f + xOffset,  0.0f + yOffset,
                       c->width + xOffset, 0.0f + yOffset};

    GLfloat uv[] = {image->left, image->top,
                    image->right, image->top,
                    image->right, image->bottom,
                    
                    image->left, image->top,
                    image->left, image->bottom,
                    image->right, image->bottom};

    glUniform1f(uniformOrtho, true);

    float position[4];
    position[0] = c->x - xOffset;
    position[1] = c->y - yOffset;
    position[2] = 0.0f;
    position[3] = 0.0f;
    glUniform4fv(uniformPosition, 1, position);

    glUniform1f(uniformAngle, c->angle);

    glUniform1f(uniformScale, c->scaleFactor);

    glUniform1f(uniformOpacity, c->opacity);

    glUniform1f(uniformWithTexture, true);

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glVertexPointer(2, GL_FLOAT, 0, verts);
//    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    //glDrawArrays(GL_TRIANGLES, 0, 6);

//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics_Class::flushImage3D(const Command* c)
{
    Image* image = ImageManager::getInstance().bindImage(c->group.c_str(),
                                                         c->name.c_str());

    GLfloat xOffset = -c->centerX * c->width;
    GLfloat yOffset = -c->centerY * c->height;

    GLfloat verts[] = {0.0f + xOffset,  c->height + yOffset, c->z,
                       c->width + xOffset, c->height + yOffset, c->z,
                       c->width + xOffset, 0.0f + yOffset, c->z,

                       0.0f + xOffset,  c->height + yOffset, c->z,
                       0.0f + xOffset,  0.0f + yOffset, c->z,
                       c->width + xOffset, 0.0f + yOffset, c->z};

    GLfloat uv[] = {image->left, image->top,
                    image->right, image->top,
                    image->right, image->bottom,
                    
                    image->left, image->top,
                    image->left, image->bottom,
                    image->right, image->bottom};

    glUniform1f(uniformOrtho, false);

    float position[4];
    position[0] = c->x - xOffset - CAMERA.getX();
    position[1] = c->y - yOffset - CAMERA.getY();
    position[2] = CAMERA.getZoom();
    position[3] = 0.0f;
    glUniform4fv(uniformPosition, 1, position);

    glUniform1f(uniformAngle, c->angle);

    glUniform1f(uniformScale, c->scaleFactor);

    glUniform1f(uniformOpacity, c->opacity);

    glUniform1f(uniformWithTexture, true);

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glVertexPointer(3, GL_FLOAT, 0, verts);
//    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    //glDrawArrays(GL_TRIANGLES, 0, 6);

//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void logShader(const char* tag, GLuint i)
{
    static const GLsizei MAXLEN = 1 << 12;
    GLsizei len = 0;
    char log[MAXLEN];
    if (i != shaderProgram)
        glGetShaderInfoLog(i, MAXLEN, &len, log);
    else
        glGetProgramInfoLog(i, MAXLEN, &len, log);
    if (len != 0)
        LOGE("%s: %s", tag, log);
}

void initShaders()
{
    shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vshader = Utils::fileToString("shaders/common.vert");
    std::string fshader = Utils::fileToString("shaders/common.frag");

    const char* v = vshader.c_str();
    const char* f = fshader.c_str();

    glShaderSource(shaderVertex, 1, &v, 0);
    glShaderSource(shaderFragment, 1, &f, 0);
    glCompileShader(shaderVertex);
    glCompileShader(shaderFragment);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, shaderVertex);
    glAttachShader(shaderProgram, shaderFragment);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    uniformOrtho = glGetUniformLocation(shaderProgram, "ortho");
    uniformAngle = glGetUniformLocation(shaderProgram, "angle");
    uniformScale = glGetUniformLocation(shaderProgram, "scale");
    uniformPosition = glGetUniformLocation(shaderProgram, "position");
    uniformColor = glGetUniformLocation(shaderProgram, "color");
    uniformOpacity = glGetUniformLocation(shaderProgram, "opacity");
    uniformWithTexture = glGetUniformLocation(shaderProgram, "withTexture");
    uniformPerspProjMat = glGetUniformLocation(
        shaderProgram, "perspProjMat"
    );
    attribVertex = glGetAttribLocation(shaderProgram, "vPosition");

    logShader("vertex shader", shaderVertex);
    logShader("fragment shader", shaderFragment);
    logShader("program", shaderProgram);
}
