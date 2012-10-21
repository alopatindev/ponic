#include "Graphics.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "ImageManager.h"
#include "Log.h"
#include "Camera.h"
#include "FontManager.h"
#include "misc/Utils.h"
#include "Assert.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Ponic";

GLhandleARB shaderVertex,
            shaderFragment,
            shaderProgram;

GLhandleARB uniformOrtho,
            uniformAngle,
            uniformScale,
            uniformPosition,
            uniformColor,
            uniformOpacity,
            uniformWithTexture,
            uniformPerspProjMat;

void initShaders();
void logShader(const char* tag, GLhandleARB i);

void Graphics_Class::init()
{
    int argc = 0;
    char** argv = 0;
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);

    glewInit();
    ASSERT(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader,
           "no GLSL support")

    initShaders();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);
    glDepthFunc(GL_NICEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.01);
    glEnable(GL_ALPHA_TEST);

    glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
}

void Graphics_Class::startFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics_Class::endFrame()
{
    flushGeomerty(m_imagesBuffer);
    flushGeomerty(m_imagesBufferTransparent);
    glutSwapBuffers();
}

void Graphics_Class::forceRedraw()
{
    glutPostRedisplay();
}

void Graphics_Class::setClip(float x, float y, float width, float height)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(x * getWidth(),
              1.0f - y * getHeight(),
              width * getWidth(),
              height * getHeight());
}

void Graphics_Class::resetClip()
{
    glDisable(GL_SCISSOR_TEST);
}

void Graphics_Class::onReshape(int width, int height)
{
    m_width = (float)width;
    m_height = (float)height;

    float perspMatrix[16];
    float aspect = m_width / m_height;
    buildPerspProjMat(perspMatrix, 45.0f, aspect, 0.1f, 100.0f);
    glUniformMatrix4fvARB(uniformPerspProjMat, 1, GL_FALSE, perspMatrix);

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

    glUniform1fARB(uniformOrtho, true);

    float position[4];
    position[0] = c->x - xOffset;
    position[1] = c->y - yOffset;
    position[2] = 0.0f;
    position[3] = 0.0f;
    glUniform4fvARB(uniformPosition, 1, position);

    glUniform1fARB(uniformAngle, c->angle);

    glUniform1fARB(uniformScale, c->scaleFactor);

    glUniform3fvARB(uniformColor, 1, c->color);

    glUniform1fARB(uniformOpacity, c->opacity);

    glUniform1fARB(uniformWithTexture, false);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, verts);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
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

    glUniform1fARB(uniformOrtho, true);

    float position[4];
    position[0] = c->x - xOffset;
    position[1] = c->y - yOffset;
    position[2] = 0.0f;
    position[3] = 0.0f;
    glUniform4fvARB(uniformPosition, 1, position);

    glUniform1fARB(uniformAngle, c->angle);

    glUniform1fARB(uniformScale, c->scaleFactor);

    glUniform1fARB(uniformOpacity, c->opacity);

    glUniform1fARB(uniformWithTexture, true);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

    glUniform1fARB(uniformOrtho, false);

    float position[4];
    position[0] = c->x - xOffset - CAMERA.getX();
    position[1] = c->y - yOffset - CAMERA.getY();
    position[2] = CAMERA.getZoom();
    position[3] = 0.0f;
    glUniform4fvARB(uniformPosition, 1, position);

    glUniform1fARB(uniformAngle, c->angle);

    glUniform1fARB(uniformScale, c->scaleFactor);

    glUniform1fARB(uniformOpacity, c->opacity);

    glUniform1fARB(uniformWithTexture, true);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void logShader(const char* tag, GLhandleARB i)
{
    static const GLsizei MAXLEN = 1 << 12;
    GLsizei len = 0;
    char log[MAXLEN];
    glGetInfoLogARB(i, MAXLEN, &len, log);
    if (len != 0)
        LOGE("%s: %s", tag, log);
}

void initShaders()
{
    shaderVertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    shaderFragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    std::string vshader = Utils::fileToString("shaders/common.vert");
    std::string fshader = Utils::fileToString("shaders/common.frag");
    const char* v = vshader.c_str();
    const char* f = fshader.c_str();

    glShaderSourceARB(shaderVertex, 1, &v, 0);
    glShaderSourceARB(shaderFragment, 1, &f, 0);
    glCompileShaderARB(shaderVertex);
    glCompileShaderARB(shaderFragment);

    shaderProgram = glCreateProgramObjectARB();

    glAttachObjectARB(shaderProgram, shaderVertex);
    glAttachObjectARB(shaderProgram, shaderFragment);

    glLinkProgramARB(shaderProgram);
    glUseProgramObjectARB(shaderProgram);

    uniformOrtho = glGetUniformLocationARB(shaderProgram, "ortho");
    uniformAngle = glGetUniformLocationARB(shaderProgram, "angle");
    uniformScale = glGetUniformLocationARB(shaderProgram, "scale");
    uniformPosition = glGetUniformLocationARB(shaderProgram, "position");
    uniformColor = glGetUniformLocationARB(shaderProgram, "color");
    uniformOpacity = glGetUniformLocationARB(shaderProgram, "opacity");
    uniformWithTexture = glGetUniformLocationARB(shaderProgram, "withTexture");
    uniformPerspProjMat = glGetUniformLocationARB(
        shaderProgram, "perspProjMat"
    );

    logShader("vertex shader", shaderVertex);
    logShader("fragment shader", shaderFragment);
    logShader("program", shaderProgram);
}
