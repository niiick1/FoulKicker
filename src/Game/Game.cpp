#include <Windows.h>
#include "Game.h"
#include <gl\GL.h>
#include <gl\glut.h>
#include "RGBAColor.h"
#include "SpriteLayer.h"

Game::Game() :
    window(800, 600, "Foul Kicker")
{
    Layer* background = new Layer();
    background->addImage("resources/img/stadium.ptm");
    background->setX(0);
    background->setY(0);

    Image* bgImg = background->getImage();

    this->scene = new Image(*bgImg);
    this->bgCopy = bgImg;
    this->layers.push_back(background);

    Layer* goalkeeper = new Layer();
    goalkeeper->addImage("resources/img/goalkeeper.ptm");
    goalkeeper->setX(399);
    goalkeeper->setY(208);

    this->layers.push_back(goalkeeper);

    Layer* wall1 = new Layer();
    wall1->addImage("resources/img/wall-1.ptm");
    wall1->setX(200);
    wall1->setY(150);

    this->layers.push_back(wall1);

    // set speed of the ball
    ball.setSpeedX(5);
    ball.setSpeedY(3);

    ballLayer.setSprite(ball.getCurrentSprite());
    ballLayer.setX(0);
    ballLayer.setY(0);

    this->goalkeeperDirection = 1;

    this->run();
}

Game::~Game()
{
    delete this->scene;
    delete this->bgCopy;

    // Properly clean the vector
    while (!this->layers.empty()) {
        delete this->layers.back();
        this->layers.pop_back();
    }
}

void Game::animateBall(int time) {
    ballLayer.saveCurrentPosition();

    int posX = ballLayer.getX() + ball.getSpeedX(),
        posY = ballLayer.getY() + ball.getSpeedY();

    if (posX > (int)window.getWidth() || posY > (int)window.getHeight()) {
        posX = -20;
        posY = -20;
    }

    ballLayer.setX(posX);
    ballLayer.setY(posY);

    if (time != 0 && time % 40 == 0) {
        ball.nextBall();
        ballLayer.setSprite(ball.getCurrentSprite());
    }

    Layer* goalkeeper = this->layers.at(1);

    /*
     * Trave Esquerda x@286
     * Trave Direita x@506
     */

    if (goalkeeper->getX() >= 506) {
        goalkeeperDirection = -1;
    } else {
        if (goalkeeper->getX() <= 286) {
            goalkeeperDirection = 1;
        }
    }

    goalkeeper->saveCurrentPosition();

    int goalkeeperPos = goalkeeper->getX();
    goalkeeperPos += 3 * goalkeeperDirection;
    goalkeeper->setX(goalkeeperPos);

    this->run();
}

void Game::run() {
    if (!this->scene) {
        this->scene = new Image(this->window.getWidth(), this->window.getHeight());
    }

    int length = this->layers.size();

    for (int i = 1; i < length; i++) {
        drawLayer(layers.at(i));
    }

    drawLayer(&ballLayer);

    // Draw ball
    ballLayer.draw(this->scene, ballLayer.getX(), ballLayer.getY());
}

void Game::drawLayer(Layer* layer) {
    Position* lastPos = layer->getLastPosition();

    /* TODO: Refactor it. This code probably should not be here.
     *
     * Redraw the part where the layer was located in the previous frame
     * so it deletes its trace.
     */
    if (lastPos) {
        int height = lastPos->getPosY() + lastPos->getHeight(),
            width = lastPos->getPosX() + lastPos->getWidth();

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

void Game::display(void) {
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, scene->getPixels());

    glFlush();
}
