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

    background->setFrameCount(1);
    background->setCurrentPos(0);
    background->setFrameHeight(background->getImage()->getHeight());
    background->setFrameWidth(background->getImage()->getWidth());
    background->setOffsetX(0);
    background->setOffsetY(0);

    this->layers.push_back(background);

    Layer* ball = new Layer();
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-kick.ptm");
    ball->setFrameCount(7);
    ball->setCurrentPos(0);
    ball->setFrameHeight(ball->getImage()->getHeight());
    ball->setFrameWidth(32);
    ball->setOffsetX(7);
    ball->setOffsetY(0);

    ball->setX(0);
    ball->setY(0);

    this->layers.push_back(ball);

    Layer* ball1 = new Layer();
    ball1->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-line.ptm");
    ball1->setFrameCount(7);
    ball1->setCurrentPos(0);
    ball1->setFrameHeight(ball1->getImage()->getHeight());
    ball1->setFrameWidth(16);
    ball1->setOffsetX(3);
    ball1->setOffsetY(0);

    ball1->setX(50);
    ball1->setY(50);

    this->layers.push_back(ball1);

    Layer* ball2 = new Layer();
    ball2->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-keeper.ptm");
    ball2->setFrameCount(7);
    ball2->setCurrentPos(0);
    ball2->setFrameHeight(ball2->getImage()->getHeight());
    ball2->setFrameWidth(12);
    ball2->setOffsetX(2);
    ball2->setOffsetY(0);

    ball2->setX(100);
    ball2->setY(100);

    this->layers.push_back(ball2);

    Layer* ball3 = new Layer();
    ball3->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-goal.ptm");
    ball3->setFrameCount(7);
    ball3->setCurrentPos(0);
    ball3->setFrameHeight(ball3->getImage()->getHeight());
    ball3->setFrameWidth(9);
    ball3->setOffsetX(2);
    ball3->setOffsetY(0);

    ball3->setX(150);
    ball3->setY(150);

    this->layers.push_back(ball3);

    this->run();
}

Game::~Game()
{
    delete this->window;
}

void Game::animateBall() {
    for (int x = 1; x < 5; x++) {
        Layer* ball = this->layers.at(x);
        ball->nextFrame();

        int posX = ball->getX() + 5,
            posY = ball->getY() + 3;

        if (posX > (int)this->window->getWidth() || posY > (int)this->window->getHeight()) {
            posX = -20;
            posY = -20;
        }

        ball->setX(posX);
        ball->setY(posY);
    }
    this->run();
}

void Game::run() {
    if (!this->scene) {
        this->scene = new Image(this->window->getWidth(), this->window->getHeight());
    }

    int length = this->layers.size();

    for (int i = 0; i < length; i++) {
        Layer* layer = this->layers.at(i);
        Image* img = layer->getImage();

        if (!img) continue;

        int startX = layer->getCurrentPos() * layer->getFrameWidth() + layer->getCurrentPos() * layer->getOffsetX(),
            startY = 0,
            height = startY + layer->getFrameHeight(),
            width = startX + layer->getFrameWidth();

        for (int y = startY; y < height; y++) {
            if (y + layer->getY() - startY >= this->scene->getHeight()) break;
            if (y + layer->getY() - startY < 0) continue;

            for (int x = startX; x < width; x++) {
                if (x + layer->getX() - startX >= this->scene->getWidth()) break;
                if (x + layer->getX() - startX < 0) continue;

                RGBAColor imgPixel(img->getPixel(x, y));

                if (imgPixel.getA() != 0) {
                    this->scene->setPixel(imgPixel.getARGB(), x + layer->getX() - startX, y + layer->getY() - startY);
                }
            }
        }
    }
}

void Game::display(void) {
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, scene->getPixels());

    glFlush();
}

