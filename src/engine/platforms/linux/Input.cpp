#include "Input.h"
#include "Application.h"
#include <GL/glut.h>

Input_Class::Input_Class()
{
    glutKeyboardUpFunc(Application::onKeyUp);
    glutKeyboardFunc(Application::onKeyDown);
    glutIgnoreKeyRepeat(true);
}

Input_Class::~Input_Class()
{
}
