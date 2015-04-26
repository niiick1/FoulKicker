#include <Windows.h>
#include "Game.h"
#include <gl\GL.h>
#include <gl\glut.h>
#include "RGBAColor.h"
#include "SpriteLayer.h"
#include "WallPlayer.h"

Game::Game() :
    window(800, 600, "Foul Kicker"), level(0)
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
    goalkeeper->addImage("resources/img/goalkeeper1.ptm");
    goalkeeper->setX(399);
    goalkeeper->setY(208);

    this->layers.push_back(goalkeeper);

    /*
     * TODO: Level layout initialization should be in
     * another place. Maybe on a file later.
     */
    level.addPlayerOnWall(Position(200, 150));
    level.addPlayerOnWall(Position(250, 150));
    level.addPlayerOnWall(Position(300, 150));
    loadLevel(level);

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
     * Trave Direita x@490
     */

    if (goalkeeper->getX() >= 490) {
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

    for (unsigned i = 0; i < wallLayers.size(); i++) {
        drawLayer(&wallLayers.at(i));
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

void Game::loadLevel(Level newLevel) {
    while (!wallLayers.empty()) {
        wallLayers.pop_back();
    }

    for (int a = 0; a < newLevel.getNumberOfPlayersOnWall(); a++) {
        Layer player;
        player.setImage(wallPlayer.getImage());

        const Position* position = level.getPlayerPosition(a);

        if (position) {
            player.setX(position->getPosX());
            player.setY(position->getPosY());
        }

        wallLayers.push_back(player);
    }
}
