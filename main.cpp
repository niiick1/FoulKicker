#include <GL/gl.h>
#include <GL/glut.h>
#include "PTMReader.h"
#include "Game.h"

#include <iostream>

using namespace std;

Game g;

void render(void) {
    g.display();
}

void animate(int t) {
    g.animateBall();

    glutPostRedisplay();
    // Reset timer
    glutTimerFunc(50, animate, 0);
}

int main(int argc, char* argv[])
{
    /*  select clearing (background) color       */
    //glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /*  initialize viewing values  */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, g.getWindow()->getWidth(), 0, g.getWindow()->getHeight(), 0, 1.0);

    glutDisplayFunc(render);

    glutTimerFunc(50, animate, 0);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}
