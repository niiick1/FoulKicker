#define _USE_MATH_DEFINES

#include <Windows.h>
#include "Game.h"
#include <gl\GL.h>
#include <gl\glut.h>
#include "RGBAColor.h"
#include "SpriteLayer.h"
#include "WallPlayer.h"

#include <math.h>
#include <iostream>

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

    // set initial speed of the ball
    ball.setSpeedX(0);
    ball.setSpeedY(0);

    ballLayer.setSprite(ball.getCurrentSprite());
    ballLayer.setX(400);
    ballLayer.setY(0);

    this->goalkeeperDirection = 1;
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

bool Game::checkForCollision() {

	bool collision = false;
	
	Layer* goalkeeper = this->layers.at(1);
	
	// GoalKeeper collision
	if ((ballLayer.getY() >= goalkeeper->getY() && ballLayer.getY() <= 224) &&
		(ballLayer.getX() >= goalkeeper->getX() && ballLayer.getX() <= goalkeeper->getX() + goalkeeper->getWidth())) {
			collision = true;
	}

	Layer wall = wallLayers.at(0);
	
	// WallLayer collision
	if (ballLayer.getY() == wall.getY() &&
		ballLayer.getX() >= wall.getX() &&
		ballLayer.getX() <= (wall.getX() + wall.getWidth() * wallLayers.size())) {
			collision = true;
	}

	// GoalLine collision
	if (Game::isBallOutOfPlay() && !Game::hasCrossedGoalLine()) {
		collision = true;
	}

	return collision;
}

void Game::animateBall(int time) {
    ballLayer.saveCurrentPosition();

	//ToDo:: Aplicar calculo de balistica
	//double v = 3.0;
	//double angulo = 30.0;
	//double a = angulo / 180.0 * M_PI;
	//double z = v * cos(a) * time;
	//double temp = z / (v * cos(a));
	//double w = z * tan(a) - 0.5 * 9.8 * (temp * temp);

	int posX = ballLayer.getX() + ball.getSpeedX(),
		posY = ballLayer.getY() + ball.getSpeedY();

    ballLayer.setX(posX);
    ballLayer.setY(posY);

    if (time != 0 && time % 40 == 0) {
        ball.nextBall();
        ballLayer.setSprite(ball.getCurrentSprite());
    }

    Layer* goalkeeper = this->layers.at(1);

	/* Detectar gol
	 * Linha do Gol y@226
	 */
	if (Game::checkForCollision()) {
		//Goal Defense
		Game::prepare();
		std::cout << "Goal Defense" << "\n";
	}

	if (Game::isBallOutOfPlay() && Game::hasCrossedGoalLine()) {
		//Goal
		Game::prepare();
		std::cout << "Goal" << "\n";
	}

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
    goalkeeperPos += 5 * goalkeeperDirection;
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

bool Game::isBallOutOfPlay() {
	return ballLayer.getY() > 225;
}

bool Game::hasCrossedGoalLine() {
	return ballLayer.getX() >= (286 + ballLayer.getWidth()) || ballLayer.getX() <= (490 - ballLayer.getWidth());
}

void Game::prepare() {
	ballLayer.setX(400);
	ballLayer.setY(0);
	ball.setSpeedY(0);
}

void Game::kick(int x, int y) {
	std::cout << "Kick " << x << "\t" << y << "\n";	

	int diffY = window.getHeight() - y;

	int initialX = ballLayer.getX();
	int finalX = initialX + ballLayer.getWidth();

	int initialY = ballLayer.getY();
	int finalY = initialY + ballLayer.getHeight();

	int axisX = finalX - x;
	int axisY = finalY - abs(diffY);

	if ((axisX >= 0 && axisX <= ballLayer.getWidth()) &&
		(axisY >= 0 && axisY <= ballLayer.getHeight())) {
		Game::prepare();
		ball.setSpeedY(1);
		std::cout << axisX << "\t" << axisY << "\n";
	}
}