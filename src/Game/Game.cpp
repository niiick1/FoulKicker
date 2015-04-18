#include "Game.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "RGBAColor.h"
#include "SpriteLayer.h"

Game::Game()
{
    this->window = new Window(800, 600, "Foul Kicker");

    Layer* background = new Layer();
    background->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/stadium.ptm");
    background->setX(0);
    background->setY(0);

    Image* bgImg = background->getImage();

    this->scene = new Image(*bgImg);
    this->bgCopy = bgImg;
    this->layers.push_back(background);

    SpriteLayer* ball = new SpriteLayer();
    ball->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-kick.ptm");

    Sprite* sprite = ball->getSprite();
    sprite->setFrameCount(7);
    sprite->setCurrentFrame(0);
    sprite->setFrameHeight(ball->getImage()->getHeight());
    sprite->setFrameWidth(32);
    sprite->setOffsetX(7);
    sprite->setOffsetY(0);

    ball->setX(0);
    ball->setY(0);

    this->layers.push_back(ball);

    SpriteLayer* ball1 = new SpriteLayer();
    ball1->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-line.ptm");
    sprite = ball1->getSprite();
    sprite->setFrameCount(7);
    sprite->setCurrentFrame(0);
    sprite->setFrameHeight(ball1->getImage()->getHeight());
    sprite->setFrameWidth(16);
    sprite->setOffsetX(3);
    sprite->setOffsetY(0);

    ball1->setX(50);
    ball1->setY(50);

    this->layers.push_back(ball1);

    SpriteLayer* ball2 = new SpriteLayer();
    ball2->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-keeper.ptm");
    sprite = ball2->getSprite();
    sprite->setFrameCount(7);
    sprite->setCurrentFrame(0);
    sprite->setFrameHeight(ball2->getImage()->getHeight());
    sprite->setFrameWidth(12);
    sprite->setOffsetX(2);
    sprite->setOffsetY(0);

    ball2->setX(100);
    ball2->setY(100);

    this->layers.push_back(ball2);

    SpriteLayer* ball3 = new SpriteLayer();
    ball3->addImage("C:/Projects/OpenGL/FoulKicker/resources/img/balls-goal.ptm");
    sprite = ball3->getSprite();
    sprite->setFrameCount(7);
    sprite->setCurrentFrame(0);
    sprite->setFrameHeight(ball3->getImage()->getHeight());
    sprite->setFrameWidth(9);
    sprite->setOffsetX(2);
    sprite->setOffsetY(0);

    ball3->setX(150);
    ball3->setY(150);

    this->layers.push_back(ball3);

    this->run();
}

Game::~Game()
{
    delete this->window;
    delete this->scene;
}

void Game::animateBall() {
    for (int x = 1; x < 5; x++) {
        Layer* ball = this->layers.at(x);

        ball->saveCurrentPosition();

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

    for (int i = 1; i < length; i++) {
        Layer* layer = this->layers.at(i);
        Position* lastPos = layer->getLastPosition();

        /* TODO: Refactor it. This code probably should not be here.
         *
         * Redraw the part where the layer was located in the previous frame
         * so it deletes its trace.
         */
        if (lastPos) {
            int layerHeight = layer->getHeight(),
                layerWidth = layer->getWidth(),
                height = lastPos->getPosY() + layerHeight,
                width = lastPos->getPosX() + layerWidth;

            for (int y = lastPos->getPosY(); y < height; y++) {
                if (y >= scene->getHeight()) break;
                if (y < 0) continue;

                for (int x = lastPos->getPosX(); x < width; x++) {
                    if (x >= scene->getWidth()) break;
                    if (x < 0) continue;

                    unsigned pixel = this->bgCopy->getPixel(x, y);
                    this->scene->setPixel(pixel, x, y);
                }
            }
        }

        layer->draw(this->scene, layer->getX(), layer->getY());
    }
}

void Game::display(void) {
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, scene->getPixels());

    glFlush();
}

