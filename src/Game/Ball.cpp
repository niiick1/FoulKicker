#include "Ball.h"
#include "PTMReader.h"

Ball::Ball() : currentBall(0)
{
    loadAssets();
}

Ball::~Ball()
{
    //dtor
}

void Ball::loadAssets() {
    PTMReader ptm;

    Sprite ball0;
    ball0.setSprite(ptm.readFile("resources/img/balls-kick.ptm"));
    ball0.setFrameCount(7);
    ball0.setCurrentFrame(0);
    ball0.setFrameHeight(ball0.getSprite()->getHeight());
    ball0.setFrameWidth(32);
    ball0.setOffsetX(7);
    ball0.setOffsetY(0);

    balls.push_back(ball0);

    Sprite ball1;
    ball1.setSprite(ptm.readFile("resources/img/balls-line.ptm"));
    ball1.setFrameCount(7);
    ball1.setCurrentFrame(0);
    ball1.setFrameHeight(ball1.getSprite()->getHeight());
    ball1.setFrameWidth(16);
    ball1.setOffsetX(3);
    ball1.setOffsetY(0);

    balls.push_back(ball1);

    Sprite ball2;
    ball2.setSprite(ptm.readFile("resources/img/balls-keeper.ptm"));
    ball2.setFrameCount(7);
    ball2.setCurrentFrame(0);
    ball2.setFrameHeight(ball2.getSprite()->getHeight());
    ball2.setFrameWidth(12);
    ball2.setOffsetX(2);
    ball2.setOffsetY(0);

    balls.push_back(ball2);

    Sprite ball3;
    ball3.setSprite(ptm.readFile("resources/img/balls-goal.ptm"));
    ball3.setFrameCount(7);
    ball3.setCurrentFrame(0);
    ball3.setFrameHeight(ball3.getSprite()->getHeight());
    ball3.setFrameWidth(9);
    ball3.setOffsetX(2);
    ball3.setOffsetY(0);

    balls.push_back(ball3);
}

void Ball::nextBall() {
    if (++currentBall >= (int)balls.size()) {
        currentBall = 0;
    }	
}