#include "Game.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "RGBAColor.h"

Game::Game()
{
    this->window = new Window(800, 600, "Foul Kicker");

    Layer* background = new Layer();
    background->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/stadium.ptm");
    background->setX(0);
    background->setY(0);

    this->layers.push_back(background);

    Layer* ball = new Layer();
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T0.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T1.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T2.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T3.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T4.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T5.ptm");
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T6.ptm");
    ball->setX(0);
    ball->setY(0);

    this->layers.push_back(ball);

    this->run();
}

Game::~Game()
{
    delete this->window;
}

void Game::animateBall() {
    Layer* ball = this->layers.at(1);
    ball->nextFrame();

    int posX = ball->getX() + 5,
        posY = ball->getY() + 3;

    if (posX > (int)this->window->getWidth() || posY > (int)this->window->getHeight()) {
        posX = -20;
        posY = -20;
    }

    ball->setX(posX);
    ball->setY(posY);
    this->run();
}

void Game::run() {
    if (!this->scene)
        this->scene = new Image(this->window->getWidth(), this->window->getHeight());

    int length = this->layers.size();
    for (int i = 0; i < length; i++) {
        Layer* layer = this->layers.at(i);
        Image* img = layer->getCurrentImage();

        if (!img) continue;

        int height = img->getHeight(),
            width = img->getWidth();

        for (int y = 0; y < height; y++) {
            if (y + layer->getY() >= scene->getHeight()) break;
            if (y + layer->getY() < 0) continue;

            for (int x = 0; x < width; x++) {
                if (x + layer->getX() >= scene->getWidth()) break;
                if (x + layer->getX() < 0) continue;

//                unsigned scenePixel = scene->getPixel(x + layer->getX(), y + layer->getY()),
//                    imgPixel = img->getPixel(x, y);

                RGBAColor imgPixel(img->getPixel(x, y));

                if (imgPixel.getA() != 0) {
                    this->scene->setPixel(imgPixel.getARGB(), x + layer->getX(), y + layer->getY());
                }
            }
        }
    }
}

void Game::display(void) {
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, scene->getPixels());

    glFlush();
}

