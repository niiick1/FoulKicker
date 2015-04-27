#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Window.h"
#include "Layer.h"
#include "Ball.h"
#include "SpriteLayer.h"
#include "Level.h"
#include "WallPlayer.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void run();
        void drawLayer(Layer* layer);
        int animateBall(int time);
        void display(void);
		void kick(int x, int y);
		void prepare();

		bool checkForCollision();
		bool isBallOutOfPlay();
		bool hasCrossedGoalLine();

        Window getWindow() { return this->window; }
    protected:
    private:
        Window window;
        Image* scene;
        Image* bgCopy;
        Level level;
        Ball ball;
        SpriteLayer ballLayer;
        WallPlayer wallPlayer;
        int goalkeeperDirection;
        std::vector<Layer*> layers;
        std::vector<Layer> wallLayers;
        std::vector<Level> levels;
        int currentTime;
		int goals;
		int attempts;
		float currentAngleDirection;

        bool nextLevel();
        void loadLevel(Level newLevel);
};

#endif // GAME_H
