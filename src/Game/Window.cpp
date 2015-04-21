#include <Windows.h>
#include "Window.h"
#include <gl\GL.h>
#include <gl\glut.h>

using std::string;

Window::Window(unsigned w, unsigned h, string title) :
    height(h), width(w), title(title)
{
    this->startGlut();
}

Window::~Window()
{
    //dtor
}

void Window::startGlut() {
    int argc = 1;
    char* argv[1] = {(char*)""};

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(this->width, this->height);

    int windowX = (glutGet(GLUT_SCREEN_WIDTH) - this->width)/2,
        windowY = (glutGet(GLUT_SCREEN_HEIGHT) - this->height)/2;

    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow(this->title.c_str());
}
