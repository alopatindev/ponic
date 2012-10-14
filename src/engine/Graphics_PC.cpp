#include "Graphics.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "ImageManager.h"
#include "Log.h"
#include "Camera.h"
#include "FontManager.h"
#include "Utils.h"

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
            uniformPerspProjMat;

void initShaders();
void logShader(const char* tag, GLhandleARB i);
void buildPerspProjMat(float *m, float fov,
                       float aspect, float znear, float zfar);

Graphics_Class::Graphics_Class()
{
    m_aspect = 1.0f;
    m_color = 1.0f;
}

Graphics_Class::~Graphics_Class()
{
}

void Graphics_Class::init()
{
    int argc = 0;
    char** argv = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);

    glewInit();
    if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    {
        LOGE("no GLSL support\n");
        exit(1);
    }

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
    glutSwapBuffers();
}

void Graphics_Class::forceRedraw()
{
    glutPostRedisplay();
}

void Graphics_Class::setClip(float x, float y, float width, float height)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);
}

void Graphics_Class::resetClip()
{
    glDisable(GL_SCISSOR_TEST);
}

void Graphics_Class::onReshape(int width, int height)
{
    m_aspect = (float)width / (float)height;

    float perspMatrix[16];
    buildPerspProjMat(perspMatrix, 45.0f, m_aspect, 0.1f, 100.0f);
    glUniformMatrix4fvARB(uniformPerspProjMat, 1, GL_FALSE, perspMatrix);

    glViewport(0, 0, width, height);
}

float Graphics_Class::getWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

float Graphics_Class::getHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}

void Graphics_Class::drawText2D(const char* fontName, int size,
                                const char* text,
                                float x, float y,
                                float r, float g, float b,
                                bool outline)
{
    // TODO
    //FontManager::getInstance().bindFont(fontName, size);
}

void Graphics_Class::drawImage2D(
    const char* group, const char* name,
    float x, float y, float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor
)
{
    Image* image = ImageManager::getInstance().bindImage(group, name);

    GLfloat xOffset = -centerX * width;
    GLfloat yOffset = -centerY * height;

    GLfloat verts[] = {0.0f + xOffset,  height + yOffset,
                       width + xOffset, height + yOffset,
                       width + xOffset, 0.0f + yOffset,
                       0.0f + xOffset,  0.0f + yOffset};

    GLfloat uv[] = {image->left, image->top,
                    image->right, image->top,
                    image->right, image->bottom,
                    image->left, image->bottom};
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    glUniform1fARB(uniformOrtho, true);

    float position[4];
    position[0] = x - xOffset;
    position[1] = y - yOffset;
    position[2] = 0.0f;
    position[3] = 0.0f;
    glUniform4fvARB(uniformPosition, 1, position);

    glUniform1fARB(uniformAngle, angle);

    glUniform1fARB(uniformScale, scaleFactor);

    glDrawArrays(GL_QUADS, 0, 4);
 
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics_Class::drawImage3D(
    const char* group, const char* name,
    float x, float y, float z,
    float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor
)
{
    Image* image = ImageManager::getInstance().bindImage(group, name);

    GLfloat xOffset = -centerX * width;
    GLfloat yOffset = -centerY * height;

    GLfloat verts[] = {0.0f + xOffset,  height + yOffset, z,
                       width + xOffset, height + yOffset, z,
                       width + xOffset, 0.0f + yOffset, z,
                       0.0f + xOffset,  0.0f + yOffset, z};

    GLfloat uv[] = {image->left, image->top,
                    image->right, image->top,
                    image->right, image->bottom,
                    image->left, image->bottom};
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
    glVertexPointer(3, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    glUniform1fARB(uniformOrtho, false);

    float position[4];
    position[0] = x - xOffset - CAMERA.getX();
    position[1] = y - yOffset - CAMERA.getY();
    position[2] = CAMERA.getZoom();
    position[3] = 0.0f;
    glUniform4fvARB(uniformPosition, 1, position);

    glUniform1fARB(uniformAngle, angle);

    glUniform1fARB(uniformScale, scaleFactor);

    glDrawArrays(GL_QUADS, 0, 4);

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
    uniformPerspProjMat = glGetUniformLocationARB(
        shaderProgram, "perspProjMat"
    );

    logShader("vertex shader", shaderVertex);
    logShader("fragment shader", shaderFragment);
    logShader("program", shaderProgram);
}

void buildPerspProjMat(float *m, float fov,
                       float aspect, float znear, float zfar)
{
    float xymax = znear * std::tan((fov * M_PI) / 180.0);
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zfar - znear;
    float q = -(zfar + znear) / depth;
    float qn = -2 * (zfar * znear) / depth;

    float w = 2 * znear / width;
    w = w / aspect;
    float h = 2 * znear / height;

    m[0]  = w;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = h;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = q;
    m[11] = -1;

    m[12] = 0;
    m[13] = 0;
    m[14] = qn;
    m[15] = 0;
}
