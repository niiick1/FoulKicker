#include "Window.h"
#include <GL/gl.h>
#include <GL/glut.h>

using std::string;

Window::Window(unsigned w, unsigned h, string title)
{
    this->height = h;
    this->width = w;
    this->title = title;

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
