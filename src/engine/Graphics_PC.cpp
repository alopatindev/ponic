#include "Graphics.h"
#include "ImageManager.h"
#include "Log.h"
#include "Camera.h"
#include <GL/glut.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Ponic";

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
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glLoadIdentity();
    gluPerspective(45.0f, m_aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(m_color, m_color, m_color);
}

void Graphics_Class::endFrame()
{
    glPopMatrix();
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

void drawText(float x, float y, const char* text,
              int size, const char* font)
{
    // TODO
}

void Graphics_Class::drawImage2D(
    const char* group, const char* name,
    float x, float y, float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor
)
{
    glPushMatrix();
    glLoadIdentity();

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

    glTranslatef(x - xOffset, y - yOffset, 0.0f);

    if (angle != 0.0f)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

    if (scaleFactor != 1.0f)
        glScalef(scaleFactor, scaleFactor, 1.0f);

    glDrawArrays(GL_QUADS, 0, 4);
 
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

void Graphics_Class::drawImage3D(
    const char* group, const char* name,
    float x, float y, float z,
    float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor
)
{
    glPushMatrix();
    glLoadIdentity();

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

    glTranslatef(x - xOffset - CAMERA.getX(),
                 y - yOffset - CAMERA.getY(),
                 CAMERA.getZoom());

    if (angle != 0.0f)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

    if (scaleFactor != 1.0f)
        glScalef(scaleFactor, scaleFactor, 1.0f);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}
