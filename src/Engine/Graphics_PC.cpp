#include "Graphics.h"
#include "ImageManager.h"
#include <GL/glut.h>
#include <Log.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Ponic";

Graphics_Class::Graphics_Class()
{
}

Graphics_Class::~Graphics_Class()
{
}

void Graphics_Class::init()
{
    int argc = 0;
    char** argv = 0;
    glutInit(&argc, argv);
    glutCreateWindow(WINDOW_TITLE);
    glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
}

void Graphics_Class::prepareFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH),
            0.0, glutGet(GLUT_WINDOW_HEIGHT),
            -1.0,
            1.0);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
}

void Graphics_Class::endFrame()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

void Graphics_Class::forceRedraw()
{
    glutPostRedisplay();
}

void Graphics_Class::setClip(float x, float y, float width, float height)
{
    glViewport(x, y, width, height);
}

void Graphics_Class::resetClip()
{
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


float Graphics_Class::getWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

float Graphics_Class::getHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}


void Graphics_Class::lookAt(float x, float y)
{
}

float Graphics_Class::getCameraX()
{
}

float Graphics_Class::getCameraY()
{
}

float Graphics_Class::setZoom(float zoom)
{
}

void drawText(float x, float y, const char* text,
              int size, const char* font)
{
    // TODO
}

void Graphics_Class::drawImage(
    const char* group, const char* name,
    float x, float y, float width, float height,
    float angle, float rCenterX, float rCenterY,
    float scaleFactor, float sCenterX, float sCenterY
)
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    Image* image = ImageManager::getInstance().bindImage(group, name);

    GLfloat verts[] = {x,         y + height,
                       x + width, y + height,
                       x + width, y,
                       x,         y};

    GLfloat uv[] = {image->left, image->top,
                    image->right, image->top,
                    image->right, image->bottom,
                    image->left, image->bottom};
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, uv);
 
    glDrawArrays(GL_QUADS, 0, 4);
 
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

bool Graphics_Class::isObjectInCamera(float x, float y,
                                      float width, float height)
{
}
