#ifndef BALL_H
#define BALL_H

#include <vector>
#include "Sprite.h"

class Ball
{
    public:
        Ball();
        virtual ~Ball();

        void nextBall();
        Sprite getCurrentSprite() { return balls.at(currentBall); }

        void setCurrentBall(int ball) { currentBall = ball; }
        int getCurrentBall() { return currentBall; }

        void setSpeedX(int speed) { speedX = speed; }
        int getSpeedX() { return speedX; }

        void setSpeedY(int speed) { speedY = speed; }
        int getSpeedY() { return speedY; }
    protected:
    private:
        void loadAssets();

        std::vector<Sprite> balls;
        int currentBall;
        int speedX;
        int speedY;
};

#endif // BALL_H
