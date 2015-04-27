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
    level.addPlayerOnWall(Position(270, 150));
    loadLevel(level);

    Level l(1);
    l.addPlayerOnWall(Position(490, 150));
    levels.push_back(l);

    Level l2(2);
    l2.addPlayerOnWall(Position(270, 150));
    l2.addPlayerOnWall(Position(320, 150));
    levels.push_back(l2);

    Level l3(3);
    l3.addPlayerOnWall(Position(440, 150));
    l3.addPlayerOnWall(Position(490, 150));
    levels.push_back(l3);

    Level l4(4);
    l4.addPlayerOnWall(Position(270, 150));
    l4.addPlayerOnWall(Position(320, 150));
    l4.addPlayerOnWall(Position(370, 150));
    levels.push_back(l4);

    Level l5(5);
    l5.addPlayerOnWall(Position(390, 150));
    l5.addPlayerOnWall(Position(440, 150));
    l5.addPlayerOnWall(Position(490, 150));
    levels.push_back(l5);

    // set initial speed of the ball
    ball.setSpeedX(0);
    ball.setSpeedY(0);

    ballLayer.setSprite(ball.getCurrentSprite());
    ballLayer.setX(400);
    ballLayer.setY(0);

    this->goalkeeperDirection = 1;

    currentTime = 1;

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

bool Game::checkForCollision() {

	bool collision = false;

	Layer* goalkeeper = this->layers.at(1);
	
	// GoalKeeper collision
	if ((ballLayer.getY() >= goalkeeper->getY() && ballLayer.getY() < 215) &&
		(ballLayer.getX() >= goalkeeper->getX() && ballLayer.getX() <= goalkeeper->getX() + goalkeeper->getWidth())) {
		collision = true;
	}

	Layer wall = wallLayers.at(0);

	// WallLayer collision
	if (ballLayer.getY() == wall.getY() &&
		ballLayer.getX() >= wall.getX() &&
		ballLayer.getX() <= (wall.getX() + wall.getWidth() * (int)wallLayers.size())) {
		collision = true;
	}

	// GoalLine collision
	if (isBallOutOfPlay() && !hasCrossedGoalLine()) {
		collision = true;
	}

	// Sideline collision
	if (ballLayer.getX() > window.getWidth() || ballLayer.getX() < 0) {
		collision = true;
	}

	return collision;
}


int Game::animateBall(int time) {
    ballLayer.saveCurrentPosition();	

	//ToDo:: Aplicar calculo de balistica
	if (currentAngleDirection > 0) {
		double v = ball.getSpeedY();
		double a = currentAngleDirection * M_PI / 180.0;
		double z = v * cos(a) * ++time;
		double temp = z / (v * cos(a));
		double w = z * tan(a) - 0.5 * 98 * (temp * temp);

		//ToDo:: Troca de Bola em Funcao do time por "v"
		if (ballLayer.getY() / 45 >= currentTime) {
			ball.nextBall();
			ballLayer.setSprite(ball.getCurrentSprite());
			currentTime++;
		}

		int posY = ballLayer.getY() + v;
		ballLayer.setX(400 + z);
		ballLayer.setY(posY);
	}

    Layer* goalkeeper = this->layers.at(1);

	/* Detectar gol
	 * Linha do Gol y@226
	 */
	if (checkForCollision()) {
		//Goal Defense
		prepare();
		Sleep(250);

		std::cout << "Goal Defense" << "\n";
		time = 0;
	}

	if (isBallOutOfPlay() && hasCrossedGoalLine()) {
		//Goal
		prepare();
		Sleep(250);

		goals++;
		std::cout << "Goal (" << goals << " / " << attempts << ")\n";
		time = 0;
		nextLevel();
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

    return time;
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
	return ballLayer.getX() >= 280 && ballLayer.getX() <= 520;
}

void Game::prepare() {
	ballLayer.setX(400);
	ballLayer.setY(0);
	ball.setSpeedX(0);
	ball.setSpeedY(2.0);
	currentAngleDirection = 0;

    currentTime = 1;
    ball.setCurrentBall(0);
    ballLayer.setSprite(ball.getCurrentSprite());
}

void Game::kick(int x, int y) {

	int diffY = window.getHeight() - y;

	int initialX = ballLayer.getX();
	int finalX = initialX + ballLayer.getWidth();

	int initialY = ballLayer.getY();
	int finalY = initialY + ballLayer.getHeight();

	int axisX = finalX - x;
	int axisY = finalY - abs(diffY);

	if (initialY == 0 &&
		(axisX >= 0 && axisX <= ballLayer.getWidth()) &&
		(axisY >= 0 && axisY <= ballLayer.getHeight())) {
		prepare();
		currentAngleDirection = abs(180 - axisX * 6);
		attempts++;
	}
}

bool Game::nextLevel() {
    if (levels.size() > 0) {
        Level l = levels.front();
        levels.erase(levels.begin());
        level = l;
        std::cout << level.getLevel() << "\n";
        // draw background
        drawLayer(layers.at(0));
        loadLevel(l);
    } else {
        std::cout << "Out of levels\n";
        return false;
    }

    return true;
}

