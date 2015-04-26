#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Window.h"
#include "Layer.h"
#include "Ball.h"
#include "SpriteLayer.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void run();
        void drawLayer(Layer* layer);
        void animateBall(int time);
        void display(void);

        Window getWindow() { return this->window; }
        Image setup();
    protected:
    private:
        Window window;
        Image* scene;
        Image* bgCopy;
        Ball ball;
        SpriteLayer ballLayer;
        int goalkeeperDirection;
        std::vector<Layer*> layers;
};

#endif // GAME_H
